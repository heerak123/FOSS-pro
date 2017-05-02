public class Painter extends JPanel{

    public static Player player;

    public Painter() {
        player = new Player(300, 300);

    }

    public void paint(Graphics g) {
        player.x++;
        g.setColor(Color.white);
        g.fillRect(player.x, player.y, 32, 32);
    }

}
