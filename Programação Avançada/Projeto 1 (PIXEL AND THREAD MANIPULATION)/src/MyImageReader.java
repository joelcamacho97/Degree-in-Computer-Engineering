import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class MyImageReader {

    public BufferedImage readImage(String path) throws IOException {
        BufferedImage result = null;

            result = ImageIO.read(new File(path));

        return result;
    }
}
