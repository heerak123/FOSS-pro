import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import java.io.*;
public class Window extends JFrame{

    private static Pane pane;

    private Window(){
        setResizable(false);
        setVisible(true);
        setBounds(0,0,350,200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    public static void main(String[] args){
        Window window = new Window();
        window.setLocationRelativeTo(null);

        pane = new Pane();
        window.add(pane);       
    }

}
