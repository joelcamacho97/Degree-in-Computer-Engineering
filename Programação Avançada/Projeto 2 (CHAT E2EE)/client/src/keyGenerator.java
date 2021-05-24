import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;
import java.io.*;
import java.security.*;
import java.security.spec.InvalidKeySpecException;
import java.security.spec.PKCS8EncodedKeySpec;
import java.security.spec.X509EncodedKeySpec;
import java.util.Base64;

public class keyGenerator {

    private KeyPairGenerator generator;
    private KeyPair pair;
    private PrivateKey private_k;
    private PublicKey public_k;

    public keyGenerator(int size){
        try {
            this.generator = KeyPairGenerator.getInstance("RSA");
            this.generator.initialize(size);
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
    }

    public void generateKeys(){
        this.pair = this.generator.generateKeyPair();
        this.setPrivate_k(pair.getPrivate());
        this.setPublic_k(pair.getPublic());
    }

    public void generateKeys(String private_key, String public_key, String key) throws IOException, NoSuchAlgorithmException, InvalidKeySpecException, NoSuchPaddingException, IllegalBlockSizeException, BadPaddingException, InvalidKeyException {

        File temp = new File(private_key);
        byte[] temp_priv_key = fileCrypto.decrypt_to_byte(key,temp);

        FileInputStream in = new FileInputStream(public_key);
        byte[] temp_pub_key = in.readAllBytes();

        PKCS8EncodedKeySpec _keySpec = new PKCS8EncodedKeySpec(temp_priv_key);
        KeyFactory keyFactory = KeyFactory.getInstance("RSA");
        this.setPrivate_k(keyFactory.generatePrivate(_keySpec));

        X509EncodedKeySpec keySpec = new X509EncodedKeySpec(temp_pub_key);
        keyFactory = KeyFactory.getInstance("RSA");
        this.setPublic_k(keyFactory.generatePublic(keySpec));
    }

    public PrivateKey getPrivate_k() {
        return private_k;
    }

    public void saveKey(String file,byte[] key){
        try{
            FileOutputStream out = new FileOutputStream(file);
            out.write(key);
            out.flush();
            out.close();
        }catch (IOException e){
            e.printStackTrace();
        }
    }

    public byte[] ecryptMessage(String messageFile, String key){
        PublicKey publicKey = null;
        try {

            X509EncodedKeySpec keySpec = new X509EncodedKeySpec(Base64.getDecoder().decode(key.getBytes()));
            KeyFactory keyFactory = KeyFactory.getInstance("RSA");
            publicKey = keyFactory.generatePublic(keySpec);

            Cipher cipher = Cipher.getInstance("RSA");
            cipher.init(Cipher.ENCRYPT_MODE,publicKey);

            //byte[] encryptedContent = Files.readAllBytes(Paths.get(messageFile));
            byte[] msg = cipher.doFinal(messageFile.getBytes());
            return msg;
            //return  new String(msg,"UTF-8");

        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        } catch (NoSuchPaddingException e) {
            e.printStackTrace();
        } catch (InvalidKeyException e) {
            e.printStackTrace();
        } catch (IllegalBlockSizeException e) {
            e.printStackTrace();
        } catch (BadPaddingException e) {
            e.printStackTrace();
        } catch (InvalidKeySpecException e) {
            e.printStackTrace();
        }
        return null;
    }

    public String decryptMessage(byte[] messageFile, PrivateKey key){
        try {
            Cipher cipher = Cipher.getInstance("RSA");
            cipher.init(Cipher.DECRYPT_MODE,key);
            //byte[] encryptedContent = Files.readAllBytes(Paths.get(messageFile));
            byte[] msg = cipher.doFinal(messageFile);
            return  new String(msg,"UTF-8");
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        } catch (NoSuchPaddingException e) {
            e.printStackTrace();
        } catch (InvalidKeyException e) {
            e.printStackTrace();
        } catch (BadPaddingException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (IllegalBlockSizeException e) {
            e.printStackTrace();
        }
        return "ERROR REATING CIPHER!!";
    }

    public PublicKey getPublic_k() {
        return public_k;
    }

    public void setPublic_k(PublicKey public_k) {
        this.public_k = public_k;
    }

    public void setPrivate_k(PrivateKey private_k) {
        this.private_k = private_k;
    }

}
