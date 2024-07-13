public class AirCond extends Product{

	//initialization of air conditioner horse power, air conditioner refrigerant type and air conditioner voltage
	private double acHP;
	private String acRefType;
	private double acVol;
	
	//parameterized constructor of AirCond class
	public AirCond(int itemNum, String prodName, int qAvai, double price, Boolean prodStat, double acHP, String acRefType, double acVol) 
	{
		super(itemNum, prodName, qAvai, price, prodStat);
		this.acHP = acHP;
		this.acRefType = acRefType;
		this.acVol = acVol;
	}
	
	//getter and setter for air conditioner horse power
	public double getAcHP() {
		return acHP;
	}

	public void setAcHP(double acHP) {
		this.acHP = acHP;
	}

	//getter and setter for air conditioner refrigerant type
	public String getAcRefType() {
		return acRefType;
	}

	public void setAcRefType(String acRefType) {
		this.acRefType = acRefType;
	}

	//getter and setter for air conditioner voltage
	public double getAcVol() {
		return acVol;
	}

	public void setAcVol(double acVol) {
		this.acVol = acVol;
	}

	//method to calculate the value of the stock of an air conditioner
	public double calStockValue(){
		return getqAvai() * getPrice();
	}
	
	//override toString() method and return info of AirCong object
	@Override
	public String toString()
	{
		return "Item number	: " + getItemNum() 
				+"\nProduct Name	: " + getProdName()
				+ "\nHorse Power	: " + acHP 
				+ "\nRefrigerant Type	: " + acRefType 
				+ "\nVoltage (V)	: " + acVol
				+ "\nQuantity Available	: " + getqAvai()
				+ "\nPrice (RM)	: " + getPrice() 
				+ "\nInventory value (RM)	: " + calStockValue()
				+ "\nProduct Status	: " + getProdStat()
				+ "\n"; 
	}
}
