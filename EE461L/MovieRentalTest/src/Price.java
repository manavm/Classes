public abstract class Price {

	public Price() {
		super();
	}
	
	protected abstract double getCharge(int daysRented);

	public abstract int getPriceCode();

	int getFrequentRenterPoints(int daysRented) {
		return 1;
	}

}