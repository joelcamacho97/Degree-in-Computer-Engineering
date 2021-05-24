import javax.crypto.BadPaddingException;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;
import java.io.File;
import java.io.IOException;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
import java.security.spec.InvalidKeySpecException;

public class Main {

    public static void main(String arg[]) throws IOException, IllegalBlockSizeException, NoSuchPaddingException, BadPaddingException, NoSuchAlgorithmException, InvalidKeyException, InvalidKeySpecException {
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
            //my_generator.generateKeys(_dir+"/private",_dir+"/public", __key); --> n será usado pq o objetivo é cada cliente ter uma chave diferente !
            my_generator.generateKeys();
            my_generator.saveKey(_dir+"/public",
                    my_generator.getPublic_k().getEncoded());
            my_generator.saveKey(_dir+"/private",
                    my_generator.getPrivate_k().getEncoded());

            File private_key = new File(_dir+"/private");
            fileCrypto.encrypt(__key,private_key,private_key);
        } else {
            my_generator.generateKeys();
            my_generator.saveKey(_dir+"/public",
                    my_generator.getPublic_k().getEncoded());
            my_generator.saveKey(_dir+"/private",
                    my_generator.getPrivate_k().getEncoded());

            File private_key = new File(_dir+"/private");
            fileCrypto.encrypt(__key,private_key,private_key);
        }

        SocketSender socket = new SocketSender(8888, my_generator);
        socket.execute();
    }
}
