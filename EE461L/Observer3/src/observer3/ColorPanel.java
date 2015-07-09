
package observer3;
 
import javax.swing.JPanel;
 
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
 
public abstract class ColorPanel extends JPanel{
    protected Color color;
 
    public ColorPanel(Color initialColor){
        this.color = initialColor;
        this.setPreferredSize(new Dimension(300, 200));
    }
 
    public void setColor(Color newColor){
        this.color = newColor;
        repaint();
    }
 
    protected void paintComponent(Graphics g){
        this.setBackground(color);
        super.paintComponent(g);
    }
}