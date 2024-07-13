public class Refrigerator extends Product
{
	//initialization of refrigerator door design, refrigerator color and refrigeraotr capacity
	private String refDoorDesg;
	private String refColor;
	private double refCap;
	
	//parameterized constructor of Refrigerator class
	public Refrigerator(int itemNum, String prodName, int qAvai, double price, Boolean prodStat, String refDoorDesg, String refColor, double refCap) 
	{
		super(itemNum, prodName, qAvai, price, prodStat);
		this.refDoorDesg = refDoorDesg;
		this.refColor = refColor;
		this.refCap = refCap;
	}

	//getter and setter for refrigerator door design
	public String getRefDoorDesg() {
		return refDoorDesg;
	}

	public void setRefDoorDesg(String refDoorDesg) {
		this.refDoorDesg = refDoorDesg;
	}

	//getter and setter for refrigerator color 
	public String getRefColor() {
		return refColor;
	}

	public void setRefColor(String refColor) {
		this.refColor = refColor;
	}

	//getter and setter for refrigerator capacity
	public double getRefCap() {
		return refCap;
	}

	public void setRefCap(double refCap) {
		this.refCap = refCap;
	}
	
	//method to calculate the value of the stock of a refrigerator
	public double calStockValue(){
		return getqAvai() * getPrice();
	}
	
	//override toString() method and return info of Refrigerator object
	@Override
	public String toString()
	{
		return "Item number	: " + getItemNum() 
				+"\nProduct Name	: " + getProdName()
				+ "\nDoor design	: " + refDoorDesg 
				+ "\nColor	: " + refColor 
				+ "\nCapacity (in Litres)	: " + refCap
				+ "\nQuantity Available	: " + getqAvai()
				+ "\nPrice (RM)	: " + getPrice() 
				+ "\nInventory value (RM)	: " + calStockValue()
				+ "\nProduct Status	: " + getProdStat()
				+ "\n"; 
	}

}
