import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import java.io.*;
import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JLayeredPane;

public class Pane extends JPanel implements ActionListener{

    private JButton next;

    public Pane(){
        setBounds(0,0,350,200);
        setVisible(true);
        setLayout(null);
        repaint();

        next = new JButton("Next");
        next.setBounds(125,125,100,30);
        next.addActionListener(this);
        add(next);

    }

    public void actionPerformed (ActionEvent e){
        Object source = e.getSource();
        if (source == next){
            Graphics g = this.getGraphics();
            drawing(g);
        }
    }

    public void paintComponent(Graphics g){
        super.paintComponent(g);
        g.drawRect(50,50,50,50);
        g.drawRect(100,50,50,50);
        g.drawRect(150,50,50,50);
        g.drawRect(200,50,50,50);
        g.drawRect(250,50,50,50);
    }

    private int times = 0;
    public void drawing(Graphics g){
        if(times<5){
            g.setColor(Color.RED);
            g.fillOval(50+times*50, 50, 50, 50);
            times++;
        }
    }

}
