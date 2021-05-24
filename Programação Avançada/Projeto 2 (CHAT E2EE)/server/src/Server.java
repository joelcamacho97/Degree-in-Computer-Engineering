import javax.crypto.BadPaddingException;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;
import java.io.File;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
import java.security.spec.InvalidKeySpecException;
import java.util.HashSet;
import java.util.Set;

public class Server {
    private Set<String> userNames = new HashSet<>();
    private Set<MACSocketServer> userThreads = new HashSet<>();

    public void execute(){
        ServerSocket server = null;
        try {
            keyGenerator my_generator = new keyGenerator(1024);

            String _dir = System.getProperty("user.dir")+"/KEYS";
            File theDir = new File(_dir);
            if (!theDir.exists()){
                theDir.mkdirs();
            }

            File f = new File(_dir+"/private");
            File f2 = new File(_dir+"/public");
            String __key = "3F657FFE4C8A3_!-";

            if((f.exists() && !f.isDirectory()) && (f2.exists() && !f2.isDirectory())) {
                my_generator.generateKeys(_dir+"/private",_dir+"/public", __key);
            } else {
                my_generator.generateKeys();
                my_generator.saveKey(_dir+"/public",
                        my_generator.getPublic_k().getEncoded());
                my_generator.saveKey(_dir+"/private",
                        my_generator.getPrivate_k().getEncoded());

                File private_key = new File(_dir+"/private");
                fileCrypto.encrypt(__key,private_key,private_key);
            }

            server = new ServerSocket(8888);

            while(true){
                Socket socket = server.accept();
                System.out.println("Started Server Socket");

                MACSocketServer newUser = new MACSocketServer(socket, this, my_generator);
                userThreads.add(newUser);
                newUser.start();

            }
        } catch (IOException e) {
            System.out.println("Error in the server: " + e.getMessage());
            e.printStackTrace();
        } catch (IllegalBlockSizeException e) {
            e.printStackTrace();
        } catch (NoSuchPaddingException e) {
            e.printStackTrace();
        } catch (BadPaddingException e) {
            e.printStackTrace();
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        } catch (InvalidKeyException e) {
            e.printStackTrace();
        } catch (InvalidKeySpecException e) {
            e.printStackTrace();
        }
    }

    void sendForUser(String msg, String User){
        for (MACSocketServer aUser : userThreads) {
            if (aUser.getUserName().equals(User)) {
                aUser.sendMessage(msg);
                break;
            }
        }
    }

    void server_broadcast(String msg, MACSocketServer excludeUser) {
        for (MACSocketServer aUser : userThreads) {
            if (aUser != excludeUser) {
                aUser.sendMessage(aUser.msgEcryptedToSocket(msg,aUser.getClient_public_key()));
            }
        }
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

    void enviarChaves(){

        for (MACSocketServer user : getUserThreads()) {


            Message myMsg = new Message("Mas2142SS!±");

            user.sendMessage(user.msgEcryptedToSocket("ENVIO_DE_CHAVES_PUBLICAS", user.getClient_public_key()));

            for (MACSocketServer all : getUserThreads()) {

                if (all != user) {
                    //String temp_publicKey = Base64.getEncoder().encodeToString(all.getMy_generator().getPublic_k().getEncoded());
                    String temp_publicKey = all.getUserName() + "USER_CHAVE" + all.getClient_public_key();
                    myMsg.createMyMACandMessage(temp_publicKey);
                    temp_publicKey = temp_publicKey + "MAC" + new String(myMsg.mac_result);
                    user.sendMessage(temp_publicKey);
                }

            }
            String FIM = "FIM_CHAVES_PUBLICAS";
            myMsg.createMyMACandMessage(FIM);
            FIM = FIM + "MAC" + new String(myMsg.mac_result);
            user.sendMessage(FIM);
        }

    }

    public Set<MACSocketServer> getUserThreads() {
        return userThreads;
    }

    void addUserName(String userName){
        userNames.add(userName);
    }

    void removeUser(String userName, MACSocketServer aUser) {
        boolean removed = userNames.remove(userName);
        if (removed) {
            userThreads.remove(aUser);
            System.out.println("The user " + userName + " quitted");
        }
    }

    public Set<String> getUserNames() {
        return userNames;
    }

    boolean hasUsers() {
        return !this.userNames.isEmpty();
    }




}
