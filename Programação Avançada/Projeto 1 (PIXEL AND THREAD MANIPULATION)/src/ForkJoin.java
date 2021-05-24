import java.awt.image.BufferedImage;
import java.util.concurrent.RecursiveTask;

public class ForkJoin extends RecursiveTask {

    private int offset_y;
    private int offset_x;
    private BufferedImage img;
    private BufferedImage temp;
    private int sectores_x;
    private int sectores_y;

    public ForkJoin (BufferedImage image, int offset_x,int offset_y, int sectores_x, int sectores_y, BufferedImage temp) {
        this.img = image;
        this.offset_x = offset_x;
        this.offset_y = offset_y;
        this.sectores_x = sectores_x;
        this.sectores_y = sectores_y;
        this.temp = temp;


    }

    public int getOffset_y() {
        return offset_y;
    }

    public int getOffset_x() {
        return offset_x;
    }

    public BufferedImage getImg() {
        return img;
    }

    public BufferedImage getTemp() {
        return temp;
    }

    public int getSectores_x() {
        return sectores_x;
    }
    public int getSectores_y() {
        return sectores_y;
    }

    public ForkJoin invoke(ForkJoin fork) {
        ImageTransformer transformer = new ImageTransformer();

        int sector_size_Width = img.getWidth() / sectores_x;
        int sector_size_Height = img.getHeight() / sectores_y;

        if(temp == null) {
            temp = transformer.removeReds(img,sector_size_Width,sector_size_Height,0,0);
            //offset_x = sector_size_Width;
            offset_y = 0;
            for (int i = 1; i<sectores_x; i++){
                BufferedImage horzTemp = transformer.removeReds(img,sector_size_Width,sector_size_Height,offset_x,0);
                temp = transformer.hor_joinBufferedImage(temp,horzTemp);
                offset_x = offset_x + sector_size_Width;
            }
            offset_y = offset_y + sector_size_Height;
        } else{

            BufferedImage temp_line = transformer.removeReds(img,sector_size_Width,sector_size_Height,0,offset_y);
            offset_x = sector_size_Width;
            for (int j = 1; j< sectores_x; j++){
                BufferedImage horzTemp = transformer.removeReds(img,sector_size_Width,sector_size_Height,offset_x,offset_y);
                temp_line = transformer.hor_joinBufferedImage(temp_line,horzTemp);
                offset_x = offset_x + sector_size_Width;
            }
            temp = transformer.vert_joinBufferedImage(temp,temp_line);
            offset_y = offset_y + sector_size_Height;

        }

        fork = new ForkJoin(img, offset_x, offset_y, sectores_x, sectores_y, temp);
        return fork;

    }

    @Override
    protected Object compute() {
        return null;
    }
}
