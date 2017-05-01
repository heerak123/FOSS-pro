import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
class DrawE extends JFrame implements ActionListener
{
    Container c;
    JMenuBar menubar;
    JMenu shape, color;
    JMenuItem circle, rectangle, line;
    JMenuItem red, green, blue, yellow;
    int col=0;
    Graphics g;
    DrawE ()
    {
        c=getContentPane ();
        menubar=new JMenuBar ();
        shape=new JMenu ("Shape");
        color=new JMenu ("Color");
        circle=new JMenuItem ("Circle");
        rectangle=new JMenuItem ("Rectangle");
        line=new JMenuItem ("Line");
        red=new JMenuItem ("Red");
        green=new JMenuItem ("Green");
        blue=new JMenuItem ("Blue");
        yellow=new JMenuItem ("Yellow");
        shape.add (circle);
        shape.add (rectangle);
        shape.add (line);
        color.add (red);
        color.add (green);
        color.add (blue);
        color.add (yellow);
        menubar.add (shape);
        menubar.add (color);        
        setJMenuBar (menubar);
        c.setLayout (new FlowLayout (0) );
        setSize (600, 600);
        setTitle ("Draw Shape");
        setVisible (true);
        circle.addActionListener (this);
        rectangle.addActionListener (this);
        line.addActionListener (this);
        red.addActionListener (this);
        green.addActionListener (this);
        blue.addActionListener (this);
        yellow.addActionListener (this);
    }
    public void actionPerformed (ActionEvent ae)
    {
        g=getGraphics ();
        if (col==1)
            g.setColor (Color.red);
        if (col==2)
            g.setColor (Color.green);
        if (col==3)
            g.setColor (Color.blue);
        if (col==4)
            g.setColor (Color.yellow);
        if (ae.getSource () == red)
            col=1;
        if (ae.getSource () == green)
            col=2;
        if (ae.getSource () == blue)
            col=3;
        if (ae.getSource () == yellow)
            col=4;
        if (ae.getSource() == circle)
        {
            g.clearRect (0, 20, 600, 600);
            g.fillOval (150, 150, 400, 400);
        }
        if (ae.getSource() == rectangle)
        {
            g.clearRect (0, 20, 600, 600);
            g.fillRect (150, 150, 400, 400);
        }
        if (ae.getSource() == line)
        {
            g.clearRect (0, 20, 600, 600);
            g.drawLine (150, 150, 400, 400);
        }
    }
    public static void main (String args [] )
    {
        new DrawE ();
    }
}
