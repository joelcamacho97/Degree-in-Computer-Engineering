import java.io.Console;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;
import java.security.KeyFactory;
import java.security.NoSuchAlgorithmException;
import java.security.PublicKey;
import java.security.spec.InvalidKeySpecException;
import java.security.spec.X509EncodedKeySpec;
import java.util.*;

public class SocketSender {

    private Socket socket;
    private DataOutputStream output;
    private DataInputStream input;
    private int port;
    private String userName;
    private keyGenerator my_generator;
    private String publicKeyServer;
    private Map<String,String> public_keys = new HashMap<String,String>();
    private boolean user_ok = true;

    public SocketSender(int port, keyGenerator my_generator){
        this.port = port;
        this.my_generator = my_generator;
    }

    public boolean isUser_ok() {
        return user_ok;
    }

    public void setUser_ok(boolean user_ok) {
        this.user_ok = user_ok;
    }

    public String msgEcryptedToSocket(String msg, String _publicKey){
        Message myMsg  = new Message("Mas2142SS!±");
        myMsg.createMyMACandMessage(msg);
        msg = msg+"MAC"+new String(myMsg.mac_result);
        return Base64.getEncoder().encodeToString(my_generator.ecryptMessage(msg, _publicKey));
    }

    public byte[] Base64_String_to_Byte (String _Base64){
        return Base64.getDecoder().decode(_Base64);
    }

    public String msgDecryptToSocket(String msg__){
        byte[] _msg = Base64_String_to_Byte(msg__);
        msg__ = my_generator.decryptMessage(_msg,my_generator.getPrivate_k());

        String mac = msg__.split("MAC")[1];
        String msg = msg__.split("MAC")[0];

        Message myMsg = new Message("Mas2142SS!±");
        myMsg.createMyMACandMessage(msg);

        if (mac.endsWith(new String(myMsg.mac_result))) {
            //System.out.println("\n#     MENSAGEM VÁLIDA     #");
        } else {
            msg = "#   MENSAGEM NÃO VÁLIDA   #";
            //System.out.println("\n#   MENSAGEM NÃO VÁLIDA   #");
        }

        return msg;
    }

    void setUserName(String userName) {
        this.userName = userName;
    }

    String getUserName() {
        return this.userName;
    }

    public String criar_hash(String msg){
        Message myMsg  = new Message("Mas2142SS!±");
        myMsg.createMyMACandMessage(msg);
        msg = msg+"MAC"+new String(myMsg.mac_result);
        return msg;
    }

    public String ler_hash(String msg__){

        String mac = msg__.split("MAC")[1];
        String msg = msg__.split("MAC")[0];

        Message myMsg = new Message("Mas2142SS!±");
        myMsg.createMyMACandMessage(msg);

        if (mac.endsWith(new String(myMsg.mac_result))) {
            //System.out.println("\n#     MENSAGEM VÁLIDA     #");
        } else {
            msg = "#   MENSAGEM NÃO VÁLIDA   #";
            //System.out.println("\n#   MENSAGEM NÃO VÁLIDA   #");
        }

        return msg;

    }

    public void execute() {
        try {
            socket = new Socket("127.0.0.1",port);
            output = new DataOutputStream(socket.getOutputStream());
            input = new DataInputStream(socket.getInputStream());

            String publicKey = Base64.getEncoder().encodeToString(my_generator.getPublic_k().getEncoded());

            System.out.println("Connected to the chat server");

            Console console = System.console();

            String userName = console.readLine("\nEnter your name: ");
            setUserName(userName);

            try {
                output.writeUTF(criar_hash(publicKey));
                setPublicKeyServer(ler_hash(input.readUTF()));
                output.writeUTF(msgEcryptedToSocket(userName, getPublicKeyServer()));
                String user_ok;
                do{
                    user_ok = msgDecryptToSocket(input.readUTF());
                    //System.out.println("resposta:: " + user_ok);
                    if(user_ok.equals("NOME DE UTILIZADOR JÁ ESCOLHIDO !!")){
                        System.out.println("NOME DE UTILIZADOR JÁ ESCOLHIDO !!");
                        userName = console.readLine("\nIntroduza outro nome: ");
                        output.writeUTF(msgEcryptedToSocket(userName, getPublicKeyServer()));
                    } else setUserName(userName);
                } while(!user_ok.equals("username_ok"));
            } catch (IOException e) {
                e.printStackTrace();
            }

            new readThread(socket, this).start();
            new writeThread(socket, this, output, my_generator).start();

        } catch (UnknownHostException ex) {
            System.out.println("Server not found: " + ex.getMessage());
        } catch (IOException ex) {
            System.out.println("I/O Error: " + ex.getMessage());
        }

    }

    public void sendMessage(String message){
        try {
            Message myMsg  = new Message("Mas2142SS!±");
            myMsg.createMyMACandMessage(message);
            message = message+"MAC"+new String(myMsg.mac_result);
            output.writeUTF(message);
            output.writeUTF("FIM");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void closeSocket(){
        try {
            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public String getPublicKeyServer() {
        return publicKeyServer;
    }

    public void setPublicKeyServer(String publicKeyServer) {
        this.publicKeyServer = publicKeyServer;
    }

    public PublicKey convString_to_key(String public_key) throws NoSuchAlgorithmException, InvalidKeySpecException {
        X509EncodedKeySpec keySpec = new X509EncodedKeySpec(Base64.getDecoder().decode(public_key.getBytes()));
        KeyFactory keyFactory = KeyFactory.getInstance("RSA");
        return keyFactory.generatePublic(keySpec);
    }

    public Map<String, String> getPublic_keys() {
        return public_keys;
    }

    public void setPublic_keys(String name, String public_keys) {
        this.public_keys.put(name, public_keys);
    }
}
