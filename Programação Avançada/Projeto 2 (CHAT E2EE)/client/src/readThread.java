import java.io.*;
import java.net.Socket;
import java.util.Scanner;

public class readThread extends Thread {

    private DataInputStream in;
    private DataOutputStream out;
    private Socket socket;
    private SocketSender client;


    public readThread(Socket socket, SocketSender client) throws IOException {
        this.socket = socket;
        this.client = client;
        in = new DataInputStream(new BufferedInputStream(this.socket.getInputStream()));
        out = new DataOutputStream(this.socket.getOutputStream());
    }

    public void run() {

        Scanner input = new Scanner(System.in);
        while (true) {
            try {

                String response = client.msgDecryptToSocket(in.readUTF());
                Console console = System.console();



                if(response.contains(" has quitted.")){
                    System.out.println("O USER [" + response.split(" has quitted.")[0] +"] SAIU DO CHAT !!!");
                    //System.out.println(response.split(" has quitted.")[0] + "<-- removido da DB");
                    client.getPublic_keys().remove(response.split(" has quitted.")[0]);
                }
                else if(response.equals("BIG_SIZE_START")){

                    //System.out.println("big_start");

                    String tempRespose = "";

                    do {
                        response = client.msgDecryptToSocket(in.readUTF());
                        if(!response.equals("BIG_SIZE_END"))
                            tempRespose +=  response;
                    } while (!response.equals("BIG_SIZE_END"));

                    System.out.print("\n" + tempRespose + "\n");

                    //System.out.println("end");

                }
                else if(response.equals("ENVIO_DE_CHAVES_PUBLICAS")){
                    //System.out.println("ENVIO_DE_CHAVES_PUBLICAS");
                    client.getPublic_keys().clear();
                    do{
                        response = in.readUTF();

                        String mac = response.split("MAC")[1];
                        String msg = response.split("MAC")[0];

                        Message myMsg = new Message("Mas2142SS!±");
                        myMsg.createMyMACandMessage(msg);

                        response = msg;
                        if (mac.endsWith(new String(myMsg.mac_result)) && !response.equals("FIM_CHAVES_PUBLICAS")) {
                            String CHAVE = msg.split("USER_CHAVE")[1];
                            String USER = msg.split("USER_CHAVE")[0];

                            //System.out.println("USER +++ "+USER);
                            //System.out.println("CHAVE +++ "+CHAVE);
                            if(!USER.equals(client.getUserName()))
                                client.setPublic_keys(USER, CHAVE);

                            //System.out.println("#     CHAVE VÁLIDA     #");
                        } else if(response.equals("FIM_CHAVES_PUBLICAS")){
                            //System.out.println("[SERVER WARNING]: "+response);
                        }else {
                            response = "#   CHAVE NÃO VÁLIDA   #";
                            //System.out.println("#   CHAVE NÃO VÁLIDA   #");
                        }
                    }
                    while (!response.equals("FIM_CHAVES_PUBLICAS"));

                } else System.out.print("\n" + response + "\n");

                if (client.getUserName() != null) System.out.print("[" + client.getUserName() + "]: ");

            } catch (IOException ex) {
                System.out.println("Error reading from server: " + ex.getMessage());
                ex.printStackTrace();
                break;
            }
        }
    }

}
