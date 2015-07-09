
public class Movie {
	private String _title;
	private int _priceCode;
	public static final int REGULAR = 0;
	public static final int NEW_RELEASE = 1;
	public static final int CHILDRENS = 2;

	public Movie(String title, int priceCode) {
		_title = title;
        _priceCode = priceCode;     
	}

	public String getTitle() {
		return _title;
	}

	public void setTitle(String _title) {
		this._title = _title;
	}

	public int get_priceCode() {
		return _priceCode;
	}

	public void set_priceCode(int _priceCode) {
		this._priceCode = _priceCode;
	}
}