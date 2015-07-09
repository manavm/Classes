package observer2;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.io.Serializable;

import javax.swing.JSlider;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

public class ComplimentaryColorPanel extends ColorPanel implements ChangeListener{
	
	private Color color;
	private JSlider hueSlider;
	private JSlider saturationSlider;
	private JSlider brightnessSlider;

	public ComplimentaryColorPanel(Color initialColor, JSlider hueSlider, JSlider saturationSlider, JSlider brightnessSlider){
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
			float complementaryHue = newHue - (float)0.5;
			if(complementaryHue < 0){
				complementaryHue = complementaryHue + 1;
			}
			Color complementaryColor = Color.getHSBColor(complementaryHue, newSaturation, newBrightness);
			// WHAT GOES HERE?
					// You need to update the two color panels with the appropriate colors
			super.setColor(complementaryColor);
		}
	}
}
