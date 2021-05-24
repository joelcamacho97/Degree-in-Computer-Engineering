import java.io.*;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Base64;
import java.util.Map;

public class writeThread extends Thread {

    private DataOutputStream writer;
    private Socket socket;
    private SocketSender client;
    private String publicKey;
    private  keyGenerator my_generator;
    private DataInputStream in;

    public writeThread(Socket socket, SocketSender socketSender, DataOutputStream output, keyGenerator my_generator) throws IOException {
        this.socket = socket;
        this.client = socketSender;
        this.writer = output;
        this.my_generator = my_generator;
        this.publicKey = Base64.getEncoder().encodeToString(my_generator.getPublic_k().getEncoded());
        in = new DataInputStream(new BufferedInputStream(this.socket.getInputStream()));

    }

    public void run() {
        Console console = System.console();
        String text;
        do {
            text = console.readLine("[" + client.getUserName() + "]: ");
            //System.out.println("enviado:: "+ text);
            if(text.contains("@")){
                ArrayList <String> User = new ArrayList<String>();
                String MSG = null;
                for (int i=1; i<text.split("@").length; i++) {
                    if(i == text.split("@").length-1){
                        if(text.split("@")[i].split(" ").length >= 2) {
                            //System.out.println("USER -->" + text.split("@")[i].split(" ")[0]);
                            User.add(text.split("@")[i].split(" ")[0]);

                            MSG = "["+client.getUserName()+"]: ";

                            int j = 0;
                            for (String msg: text.split("@")[i].split(" ")) {
                                if(j > 0) MSG += msg+" ";
                                j++;
                            }

                        } else {
                            System.out.println("PARA ENVIAR A MSG PARA UM USER ESPECIFICO USE::");
                            System.out.println("@user1 @userN MSG");
                        }

                    } else {
                        //System.out.println("USER -->"+text.split("@")[i]);
                        User.add(text.split("@")[i]);
                    }
                }
                if(MSG != null){

                    for (String aUSER : User) {
                        try {
                            aUSER = aUSER.replace(" ","");
                            String _key = client.getPublic_keys().get(aUSER);
                            if(_key != null){
                                limite_msg("["+client.getUserName()+"]: " + MSG, _key, aUSER);


                            } else {
                                System.out.println("O USER ["+aUSER+"] NÃO EXISTE (SÓ NÃO SERÁ ENVIADO PARA ESTE USER)!!");
                            }
                        } catch (Exception e) {
                            e.printStackTrace();
                        }
                    }
                }
            } else{
                for (Map.Entry<String, String> me : client.getPublic_keys().entrySet()) {
                    try {
                        limite_msg("["+client.getUserName()+"]: " + text, me.getValue(), me.getKey());

                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            }

        } while (!text.equals("bye"));

        try {
            socket.close();
        } catch (IOException ex) {

            System.out.println("Error writing to server: " + ex.getMessage());
        }
    }

    public void limite_msg(String MSG, String key, String meKey) throws IOException {

        if(MSG.getBytes().length > (117 - 69)){
            writer.writeUTF(client.msgEcryptedToSocket("SEND_FOR"+meKey, client.getPublicKeyServer()));
            writer.writeUTF(client.msgEcryptedToSocket("BIG_SIZE_START", key));
            String msgTEMP = "";
            for (int i = 0; i< MSG.length(); i++) {
                if(msgTEMP.length()<=10){
                    msgTEMP += MSG.charAt(i);
                } else {
                    //System.out.println(msgTEMP);
                    writer.writeUTF(client.msgEcryptedToSocket("SEND_FOR"+meKey, client.getPublicKeyServer()));
                    writer.writeUTF(client.msgEcryptedToSocket(msgTEMP, key));
                    msgTEMP = "";
                    msgTEMP += MSG.charAt(i);
                }
            }
            writer.writeUTF(client.msgEcryptedToSocket("SEND_FOR"+meKey, client.getPublicKeyServer()));
            writer.writeUTF(client.msgEcryptedToSocket(msgTEMP, key));
            writer.writeUTF(client.msgEcryptedToSocket("SEND_FOR"+meKey, client.getPublicKeyServer()));
            writer.writeUTF(client.msgEcryptedToSocket("BIG_SIZE_END", key));
        } else {
            writer.writeUTF(client.msgEcryptedToSocket("SEND_FOR"+meKey, client.getPublicKeyServer()));
            writer.writeUTF(client.msgEcryptedToSocket(MSG, key));
        }
    }

}
