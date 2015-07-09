package observer2;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;

import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

public class OriginalColorPanel extends ColorPanel implements ChangeListener{
	protected Color color;
	protected JSlider hueSlider;
	protected JSlider saturationSlider;
	protected JSlider brightnessSlider;

	public OriginalColorPanel(Color initialColor, JSlider hueSlider, JSlider saturationSlider, JSlider brightnessSlider){
		super(initialColor);
		this.hueSlider = hueSlider;
		this.saturationSlider = saturationSlider;
		this.brightnessSlider = brightnessSlider;
		this.setPreferredSize(new Dimension(300, 200));
		hueSlider.addChangeListener(this);
		saturationSlider.addChangeListener(this);
		brightnessSlider.addChangeListener(this);
	}

	public void setColor(Color newColor){
		this.color = newColor;
		repaint();
	}

	protected void paintComponent(Graphics g){
		this.setBackground(color);
		super.paintComponent(g);
	}

	public void stateChanged(ChangeEvent e){
		if(hueSlider != null && saturationSlider != null && brightnessSlider != null){
			float newHue = (float)hueSlider.getValue()/100;
			float newSaturation = (float)saturationSlider.getValue()/100;
			float newBrightness = (float)brightnessSlider.getValue()/100;
			Color newColor = Color.getHSBColor(newHue, newSaturation, newBrightness);
			// WHAT GOES HERE?
					// You need to update the two color panels with the appropriate colors
			super.setColor(newColor);
		}
	}
}
