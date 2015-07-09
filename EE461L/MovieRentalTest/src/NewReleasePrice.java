public class NewReleasePrice extends Price {
    public int getPriceCode() {
        return Movie.NEW_RELEASE;
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
    
    @Override
	int getFrequentRenterPoints(int daysRented) {
		int frequentRenterPoints=1;
		// add bonus for a two day new release rental
		if (daysRented > 1) frequentRenterPoints++;
		return frequentRenterPoints;
	}
}