import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.util.ArrayList;
import java.util.concurrent.locks.ReentrantLock;

public class Master extends Thread {

    private ReentrantLock lock1 = new ReentrantLock();

    private int offset_y;
    private int offset_x;
    private BufferedImage img;
    private BufferedImage temp;
    private int sectores_x;
    private int sectores_y;
    private int id;
    private JPanel panel;
    private JFrame frame;
    private BufferedImage horzTemp;
    private BufferedImage temp_line;


    public Master(BufferedImage image, int sectores_x, int sectores_y, JPanel panel, JFrame frame) throws InterruptedException {
        this.img = image;
        this.sectores_x = sectores_x;
        this.sectores_y = sectores_y;
        this.panel = panel;
        this.frame = frame;

    }



    public BufferedImage getTemp() {
        return temp;
    }

    @Override
    public void run() {
        ImageTransformer transformer = new ImageTransformer();

        int sector_size_Width = img.getWidth()/sectores_x;
        int sector_size_Height = img.getHeight() / sectores_y;

        ArrayList <iThread> _horline = new ArrayList<>();

        for (int i = 1; i<sectores_y;i++) {
            if (temp == null) {
                iThread temp1 = new iThread(transformer.removeReds(img, sector_size_Width, sector_size_Height, 0, 0));
                temp1.start();
                //_temp.add(temp1);

                offset_y = 0;
                for (int m = 1; m < sectores_x; m++) {

                    iThread horzTemp1 = new iThread(transformer.removeReds(img, sector_size_Width, sector_size_Height, offset_x, 0));
                    horzTemp1.start();
                    _horline.add(horzTemp1);
                    offset_x = offset_x + sector_size_Width;
                }

                try {
                    temp1.join();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                temp = temp1.getEdit();
                for (int m = 0; m < _horline.size(); m++) {
                    try {
                        _horline.get(m).join();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                    temp = transformer.hor_joinBufferedImage(temp, _horline.get(m).getEdit());
                }

                offset_y = offset_y + sector_size_Height;
            } else {

                iThread temp_line1 = new iThread(transformer.removeReds(img, sector_size_Width, sector_size_Height, 0, offset_y));
                temp_line1.start();

                offset_x = sector_size_Width;
                _horline.clear();
                for (int j = 1; j < sectores_x; j++) {
                    iThread _horzTemp = new iThread(transformer.removeReds(img, sector_size_Width, sector_size_Height, offset_x, offset_y));
                    _horzTemp.start();
                    _horline.add(_horzTemp);
                    offset_x = offset_x + sector_size_Width;
                }

                try {
                    temp_line1.join();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                temp_line = temp_line1.getEdit();
                for (int j = 0; j < _horline.size(); j++) {
                    try {
                        _horline.get(j).join();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                    temp_line = transformer.hor_joinBufferedImage(temp_line, _horline.get(j).getEdit());
                }
                temp = transformer.vert_joinBufferedImage(temp, temp_line);
                offset_y = offset_y + sector_size_Height;

            }
        }
    }
}

