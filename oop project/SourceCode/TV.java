public class TV extends Product
{
	//initialization of TV screen type, TV resolution and TV display size
	private String tvScrTyp;
	private String tvRes;
	private double tvDisSize;
	
	//parameterized constructor of TV class
	public TV(int itemNum, String prodName, int qAvai, double price, Boolean prodStat, String tvScrTyp, String tvRes, double tvDisSize)
	{
		super(itemNum, prodName, qAvai, price, prodStat);
		this.tvScrTyp = tvScrTyp;
		this.tvRes = tvRes;
		this.tvDisSize = tvDisSize;
	}

	//getter and setter for TV screen type
	public String getTvScrTyp() {
		return tvScrTyp;
	}

	public void setTvScrTyp(String tvScrTyp) {
		this.tvScrTyp = tvScrTyp;
	}

	//getter and setter for TV resolution
	public String getTvRes() {
		return tvRes;
	}

	public void setTvRes(String tvRes) {
		this.tvRes = tvRes;
	}

	//getter and setter for TV display size
	public double getTvDisSize() {
		return tvDisSize;
	}

	public void setTvDisSize(double tvDisSize) {
		this.tvDisSize = tvDisSize;
	}
	
	//method to calculate the value of the stock of a TV
	public double calStockValue(){
		return getqAvai() * getPrice();
	}
	
	//override toString() method and return the info of TV object
	@Override
	public String toString()
	{
		return "Item number	: " + getItemNum() 
				+"\nProduct Name	: " + getProdName()
				+ "\nScreen type	: " + tvScrTyp 
				+ "\nResolution	: " + tvRes 
				+ "\nDisplay size	: " + tvDisSize
				+ "\nQuantity Available	: " + getqAvai()
				+ "\nPrice (RM)	: " + getPrice() 
				+ "\nInventory value (RM)	: " + calStockValue() 
				+ "\nProduct Status	: " + getProdStat()
				+ "\n"; 
	}

}
