
class Rental {
    private Movie _movie;
	private int _daysRented;
    public Rental(DateRange range, Movie movie) {
    	_movie = movie;
        _daysRented = (int)((range.getEnd().getTime() - range.getStart().getTime()) / (1000 * 60 * 60 * 24));
    }
    public int getDaysRented() {
        return _daysRented;
    }

    public String getTitle() {
        return _movie.getTitle();
    }
    
    public int getPriceCode() {
        return _movie.get_priceCode();
    }
	double getCharge() {
		//determine amounts for each line
	    double thisAmount = 0;          
		switch (getPriceCode()) {
		case Movie.REGULAR:
		    thisAmount += 2;
		    if (getDaysRented() > 2) {
		        thisAmount += (getDaysRented() - 2) * 1.5;
		    }
		    break;
		case Movie.NEW_RELEASE:
		    thisAmount += getDaysRented() * 3;
		    break;
		case Movie.CHILDRENS:
		    thisAmount += 1.5;
		    if (getDaysRented() > 3) {
		        thisAmount += (getDaysRented() - 3) * 1.5;
		    }
		    break;
		}
		return thisAmount;
	}
}
