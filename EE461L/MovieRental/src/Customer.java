import java.util.Enumeration;
import java.util.Vector;

class Customer {
    private String _name;
    private Vector<Rental> _rentals = new Vector<Rental>();

    public Customer(String name) {
        _name = name;
    }

    public void addRental(Rental arg) {
        _rentals.addElement(arg);
    }

    public String getName() {
        return _name;
    }

    public String statement() {
        double totalAmount = 0;
        int frequentRenterPoints = 0;
        StringBuilder result = new StringBuilder("Rental Record for " + getName() + "\n");

        for (Rental each : _rentals) {
            
            double thisAmount = amountFor(each);
            // add frequent renter points
            frequentRenterPoints ++;
            // add bonus for a two day new release rental
            if ((each.getPriceCode() == Movie.NEW_RELEASE)
                    && each.getDaysRented() > 1) frequentRenterPoints++;

            //show figures for this rental
            result.append("\t").append(each.getTitle());
            result.append("\t").append(String.valueOf(thisAmount));
            result.append("\n");

            totalAmount += thisAmount;				
        }

        //add footer lines
        result.append("Amount owed is ").append(String.valueOf(totalAmount));
        result.append("\n");
        result.append("You earned ").append(String.valueOf(frequentRenterPoints));
        result.append(" frequent renter points");
        return result.toString();
    }

	/**
	 * @deprecated Use {@link Rental#getCharge()} instead
	 */
	private double amountFor(Rental aRental) {
		return aRental.getCharge();
	}
}
