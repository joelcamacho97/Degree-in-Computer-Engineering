import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {

        Scanner myObj = new Scanner(System.in);

        System.out.println("Introduza aqui o nome da imagem que pertende abrir _");
        System.out.println("esta deverá estar dentro da pasta do projeto :");

        Boolean ___path = true;
        BufferedImage image = null;

        while(___path) {
            String __path = myObj.next();
            Boolean erro = false;
            try {
                MyImageReader reader = new MyImageReader();
                image = reader.readImage(__path);

            } catch (Exception e) {
                System.out.println("Imagem inexistente tente novamente !!!");
                erro = true;
            }
            if(erro == false) ___path = false;
        }

        final BufferedImage finalImage = image;

        for (int i = 1;i<=image.getWidth();i++) {
            for (int j = 1;j<=image.getHeight();j++) {
                if(image.getWidth()%i == image.getHeight()%j){
                    if(image.getWidth()%i == 0 && image.getHeight()%j == 0){
                        System.out.println("Sector(x) ==> "+i+" Sector(y) ==>"+j);
                    }
                }
            }
        }

        Boolean OI = true;
        int sectors_x = 0;
        int sectors_y = 0;
        while (OI){
            System.out.println("Insira a quantidade de sectores :: ");
            System.out.print("Sectores(X) ==> ");
            sectors_x = myObj.nextInt();
            System.out.print("Sectores(Y) ==> ");
            sectors_y = myObj.nextInt();

            for (int i = 1;i<=image.getWidth();i++) {
                for (int j = 1;j<=image.getHeight();j++) {
                    if(image.getWidth()%i == image.getHeight()%j){
                        if(image.getWidth()%i == 0 && image.getHeight()%j == 0){
                            if(i == sectors_x && j == sectors_y) {
                                OI = false;
                                break;
                            }
                        }
                    }
                }
            }
        }

        final int finalSectors_x = sectors_x;
        final int finalSectors_y = sectors_y;

        JFrame frame = new JFrame("PROJETO 1");
        JPanel panel =  new JPanel();
        frame.getContentPane();
        panel.setLayout(null);



        //åframe.getContentPane().add(new Test());
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(1250, 830);
        frame.setMinimumSize(new Dimension(985, 830));
        frame.setVisible(true);

        JButton b=new JButton("Pipelining");
        b.setBounds(25, 25,220,60);

        JButton dd=new JButton("Fork-Join");
        dd.setBounds(245, 25,220,60);

        JButton gg=new JButton("Master/Slave");
        gg.setBounds(465, 25,220,60);

        JButton aa=new JButton("IMAGEM SIMPLES");
        aa.setBounds(685, 25,220,60);

        JButton bb=new JButton("RESET");
        bb.setBounds(905,25,220,60);

        frame.add(aa);
        frame.add(bb);
        frame.add(dd);
        frame.add(b);
        frame.add(gg);
        frame.add(panel);

        frame.repaint();


        b.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {

                long start = System.currentTimeMillis();

                pipelining [] pipe = new pipelining[finalSectors_y];

                int sector_size_Width = finalImage.getWidth() / finalSectors_x;

                int offset_x = sector_size_Width;
                int offset_y = 0;

                try {
                    pipe[0] = new pipelining(finalImage, offset_x, offset_y, finalSectors_x, finalSectors_y, null);
                    pipe[0].start();
                    pipe[0].join();
                    for (int i = 1; i<pipe.length;i++){
                        pipe[i] = new pipelining(finalImage, pipe[i-1].getOffset_x(), pipe[i-1].getOffset_y(), finalSectors_x, finalSectors_y, pipe[i-1].getTemp());
                        pipe[i].start();
                        pipe[i].join();
                    }
                } catch (InterruptedException interruptedException) {
                    interruptedException.printStackTrace();
                }

                long elapsedTimeMillis = System.currentTimeMillis()-start;

                System.out.println("O PIPELINING demorou " + elapsedTimeMillis + "ms para ser finalizado");

                ImageIcon icon = new ImageIcon(pipe[finalSectors_y-1].getTemp());
                JScrollPane l = new JScrollPane(new JLabel(icon));
                l.setBounds(25, 100, pipe[finalSectors_y-1].getTemp().getWidth(), pipe[finalSectors_y-1].getTemp().getHeight());
                l.setSize(pipe[finalSectors_y-1].getTemp().getWidth(),650);
                panel.add(l);
                frame.add(panel);
                SwingUtilities.updateComponentTreeUI(frame);

            }
        });

        gg.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent gg) {

                long start = System.currentTimeMillis();

                int sector_size_Width = finalImage.getWidth() / finalSectors_x;
                Master m = null;
                try {
                    m = new Master(finalImage, finalSectors_x, finalSectors_y, panel, frame);
                    m.start();
                    m.join();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }



                ImageIcon icon = new ImageIcon(m.getTemp());
                JScrollPane l = new JScrollPane(new JLabel(icon));
                l.setBounds(25, 100, m.getTemp().getWidth(),m.getTemp().getHeight());
                l.setSize(m.getTemp().getWidth(),650);
                panel.add(l);
                frame.add(panel);
                SwingUtilities.updateComponentTreeUI(frame);



                long elapsedTimeMillis = System.currentTimeMillis()-start;

                System.out.println("O Master/Slave demorou " + elapsedTimeMillis + "ms para ser finalizado");

            }
        });

        dd.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent dd) {

                long start = System.currentTimeMillis();

                int sector_size_Width = finalImage.getWidth() / finalSectors_x;
                int offset_x = sector_size_Width;
                int offset_y = 0;

                ForkJoin _fork = new ForkJoin(finalImage, offset_x, offset_y, finalSectors_x, finalSectors_y, null);

                for (int i=0;i<finalSectors_y;i++) {
                    _fork = _fork.invoke(_fork);
                }

                long elapsedTimeMillis = System.currentTimeMillis()-start;
                System.out.println("O FORK/JOIN demorou " + elapsedTimeMillis + "ms para ser finalizado");

                ImageIcon icon = new ImageIcon(_fork.getTemp());
                JScrollPane l = new JScrollPane(new JLabel(icon));
                l.setBounds(25, 100, _fork.getTemp().getWidth(), _fork.getTemp().getHeight());
                l.setSize(_fork.getTemp().getWidth(),650);
                panel.add(l);
                frame.add(panel);
                SwingUtilities.updateComponentTreeUI(frame);

            }
        });

        bb.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent bb) {
                frame.remove(panel);
                panel.removeAll();
                SwingUtilities.updateComponentTreeUI(frame);
                frame.repaint();
            }
        });

        aa.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent aa) {


                ImageIcon icon = new ImageIcon(finalImage);
                JScrollPane l = new JScrollPane(new JLabel(icon));
                l.setBounds(25, 100, finalImage.getWidth(), finalImage.getHeight());
                l.setSize(finalImage.getWidth(),650);
                panel.add(l);
                frame.add(panel);
                SwingUtilities.updateComponentTreeUI(frame);

            }
        });



    }


}
