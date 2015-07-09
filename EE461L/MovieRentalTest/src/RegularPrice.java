public class RegularPrice extends Price {
    @Override
	public int getPriceCode() {
        return Movie.REGULAR;
    }

    protected double getCharge(int daysRented) {
	    //determine amounts for each line
	    double result = 0;
	        result += 1.5;
	        if (daysRented > 3) {
	            result += (daysRented - 3) * 1.5;
	        }
	        
	    return result;
    }	
}