package observer3;
 
import java.awt.Color;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
 
import javax.swing.JSlider;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
 
public class ComplimentaryColorPanel extends ColorPanel implements PropertyChangeListener {
 
    protected OriginalColorPanel originalColorPanel;
     
    public ComplimentaryColorPanel(OriginalColorPanel originalColorPanel) {
        super(originalColorPanel.color);
        Color panelColor = originalColorPanel.color;
        invertColors(panelColor);
        this.originalColorPanel = originalColorPanel;
        originalColorPanel.addPropertyChangeListener(this);
    }
 
    public void invertColors(Color panelColor){
    	float[] HSB = new float[3]; 
        Color.RGBtoHSB(panelColor.getRed(), panelColor.getGreen(), panelColor.getBlue(), HSB);
        float hue = HSB[0] - (float)0.5;
        if(hue < 0)
            hue = hue + 1; 
        Color compColor = Color.getHSBColor(hue, HSB[1], HSB[2]); 
        super.setColor(compColor);
    }
    
    @Override
    public void propertyChange(PropertyChangeEvent evt) {
        // TODO Auto-generated method stub
        OriginalColorPanel panelColorPanel = (OriginalColorPanel) evt.getSource();
        Color panelColor = panelColorPanel.color;
        invertColors(panelColor);
         
    }
}