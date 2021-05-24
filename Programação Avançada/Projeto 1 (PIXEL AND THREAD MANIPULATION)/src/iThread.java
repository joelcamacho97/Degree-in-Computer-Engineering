import java.awt.image.BufferedImage;

public class iThread extends Thread{

    private BufferedImage edit;

    public iThread(BufferedImage removeReds) {

        this.edit = removeReds;

    }

    public BufferedImage getEdit() {
        return edit;
    }
}
