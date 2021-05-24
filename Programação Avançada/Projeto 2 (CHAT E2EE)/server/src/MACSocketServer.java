import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.util.Base64;

public class MACSocketServer extends Thread {

    private final DataInputStream in;
    private final DataOutputStream out;
    private final Socket socket;
    private final Server server;
    private String userName;
    private String Client_public_key;
    private keyGenerator my_generator;

    public MACSocketServer(Socket socket, Server server, keyGenerator my_generator) throws IOException {
        this.socket = socket;
        this.server = server;
        this.my_generator = my_generator;

        in  = new DataInputStream(socket.getInputStream());
        out = new DataOutputStream(socket.getOutputStream());
        Client_public_key = null;
    }

    public byte[] Base64_String_to_Byte (String _Base64){
        return Base64.getDecoder().decode(_Base64);
    }

    public String msgEcryptedToSocket(String msg, String _publicKey){
        Message myMsg  = new Message("Mas2142SS!±");
        myMsg.createMyMACandMessage(msg);
        msg = msg+"MAC"+new String(myMsg.mac_result); //--> MSG COM A HASH PARA CONFIRMAR A INTEGRIDADE (SIMETRICA)
        return Base64.getEncoder().encodeToString(my_generator.ecryptMessage(msg, _publicKey)); //--> cryp com a chave publica (ASSIMETRICA)
    }

    public String msgDecryptToSocket(String msg__){
        byte[] _msg = Base64_String_to_Byte(msg__);
        msg__ = my_generator.decryptMessage(_msg,my_generator.getPrivate_k());

        String mac = msg__.split("MAC")[1];
        String msg = msg__.split("MAC")[0];

        //System.out.println(mac);
        //System.out.println(msg);

        Message myMsg = new Message("Mas2142SS!±");
        myMsg.createMyMACandMessage(msg);

        if (mac.endsWith(new String(myMsg.mac_result))) {
            System.out.println("#     MENSAGEM VÁLIDA     #");
        } else {
            msg = "#   MENSAGEM NÃO VÁLIDA   #";
            System.out.println("#   MENSAGEM NÃO VÁLIDA   #");
        }

        return msg;
    }


        public void run() {
        userName = null;
        String serverMessage;

        try {
            String pessoasOnline = "Os utilizadores online são:\n";
            out.writeUTF(server.criar_hash(Base64.getEncoder().encodeToString(my_generator.getPublic_k().getEncoded())));

            client_public_key(server.ler_hash(in.readUTF()));

            boolean __user = true;
            while(__user){
                __user = false;
                userName = msgDecryptToSocket(in.readUTF());
                for(String users : server.getUserNames()){
                    System.out.println(users.equals(userName));
                    if(users.equals(userName)){
                        __user = true;
                        out.writeUTF(msgEcryptedToSocket("NOME DE UTILIZADOR JÁ ESCOLHIDO !!", getClient_public_key()));
                        break;
                    }
                }
                if(__user == false){
                    out.writeUTF(msgEcryptedToSocket("username_ok", getClient_public_key()));
                }

            }

            server.addUserName(userName);

            printUsers();

            server.enviarChaves();
            out.writeUTF(msgEcryptedToSocket(pessoasOnline, getClient_public_key()));
            for (int i=0;i<server.getUserNames().size(); i++){
                if(server.getUserNames().toArray()[i] != userName){
                    pessoasOnline = "--> "+server.getUserNames().toArray()[i]+"\n";
                    out.writeUTF(msgEcryptedToSocket(pessoasOnline, getClient_public_key()));
                }
            }

            serverMessage = "New user connected: " + userName;
            server.server_broadcast(serverMessage, this);

            String clientMessage;

            do {

                clientMessage = msgDecryptToSocket(in.readUTF());
                clientMessage = clientMessage.split("SEND_FOR")[1];
                String clientMessageFOR = in.readUTF();

                server.sendForUser(clientMessageFOR, clientMessage);

                if(clientMessage.equals("@?")){

                    server.enviarChaves();
                    pessoasOnline = "Os utilizadores online são:\n";
                    out.writeUTF(msgEcryptedToSocket(pessoasOnline, getClient_public_key()));
                    for (int i=0;i<server.getUserNames().size(); i++){
                        if(server.getUserNames().toArray()[i] != userName){
                            pessoasOnline = "--> "+server.getUserNames().toArray()[i]+"\n";
                            out.writeUTF(msgEcryptedToSocket(pessoasOnline, getClient_public_key()));
                        }
                    }
                    continue;
                }

                /*if(clientMessage.contains("@")){
                    String _clientMessage = clientMessage.replace("@","");
                    if(!clientMessage.equals("@"+_clientMessage)){
                        server.forMySelf("ERRO: Apenas pode usar '@user'",this);
                        continue;
                    }
                }*/

                //server.broadcast(serverMessage, this);



            } while (!clientMessage.equals("bye"));

            server.removeUser(userName, this);
            socket.close();
            in.close();

            serverMessage = userName + " has quitted.";
            server.server_broadcast(serverMessage, this);
            server.enviarChaves();

        } catch (IOException e) {
            //e.printStackTrace();
            try {
                // close connection
                serverMessage = userName + " has quitted.";
                server.server_broadcast(serverMessage, this);
                server.removeUser(userName, this);
                socket.close();
                in.close();



            } catch (IOException ioException) {
                ioException.printStackTrace();
            }
        }
    }

    void printUsers() {
        if (server.hasUsers()) {
            System.out.println("Connected users: " + server.getUserNames());
        } else {
            System.out.println("No other users connected");
        }
    }

    void sendMessage(String message) {
        try {
            out.writeUTF(message);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public String getUserName() {
        return userName;
    }

    public Socket getSocket() {
        return socket;
    }

    public String getClient_public_key() {
        return Client_public_key;
    }

    public void client_public_key(String temp_public_key)  {
        Client_public_key = temp_public_key;
    }

    public keyGenerator getMy_generator() {
        return my_generator;
    }
}
