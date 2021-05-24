import java.awt.*;
import java.awt.image.BufferedImage;

public class ImageTransformer{

    public BufferedImage removeReds(BufferedImage image,int width, int height, int offset_x,int offset_y){
        Color c;

        BufferedImage resultado = new BufferedImage(width,height,BufferedImage.TYPE_INT_RGB);

        int media_r = 0;
        int media_g = 0;
        int media_b = 0;
        int media = 1;

        for(int i=0;i<width;i++){
            for(int j=0;j<height;j++){
                //System.out.println("Working on "+(i+offset_x)+"   "+(j+offset_y));
                c = new Color(image.getRGB(i + offset_x,j + offset_y));
                int r = c.getRed();
                int g = c.getGreen();
                int b = c.getBlue();

                media_r += r;
                media_g += g;
                media_b += b;

                media++;
            }
        }

        //System.out.print("R:"+media_r/(media.length-1)+" G:"+media_g/(media.length-1)+" B:"+media_b/(media.length-1));

        for(int i=0;i<width;i++){
            for(int j=0;j<height;j++) {
                resultado.setRGB(i,j,new Color(media_r/(media),media_g/(media),media_b/(media)).getRGB());
            }
        }

        //System.out.println("Acabei a conversão");
        return resultado;
    }

    public  BufferedImage hor_joinBufferedImage(BufferedImage img1,
                                                  BufferedImage img2) {
        int offset = 0; // espaçamento
        int width = img1.getWidth() + img2.getWidth() + offset;
        int height = Math.max(img1.getHeight(), img2.getHeight());
        BufferedImage newImage = new BufferedImage(width, height,
                BufferedImage.TYPE_INT_RGB);
        Graphics2D g2 = newImage.createGraphics();
        Color oldColor = g2.getColor();
        g2.setPaint(Color.BLACK);
        g2.fillRect(0, 0, width, height);
        g2.setColor(oldColor);
        g2.drawImage(img1, null, 0, 0);
        g2.drawImage(img2, null, img1.getWidth() + offset, 0);
        g2.dispose();
        return newImage;
    }

    public  BufferedImage vert_joinBufferedImage(BufferedImage img1,
                                            BufferedImage img2) {
        int offset = 0;
        int height = img1.getHeight() + img2.getHeight() + offset;
        int width = Math.max(img1.getWidth(), img2.getWidth());
        BufferedImage newImage = new BufferedImage(width, height,
                BufferedImage.TYPE_INT_RGB);
        Graphics2D g2 = newImage.createGraphics();
        Color oldColor = g2.getColor();
        g2.setPaint(Color.BLACK);
        g2.fillRect(0, 0, width, height);
        g2.setColor(oldColor);
        g2.drawImage(img1, null, 0, 0);
        g2.drawImage(img2, null, 0, img1.getHeight() + offset);
        g2.dispose();
        return newImage;
    }
}
