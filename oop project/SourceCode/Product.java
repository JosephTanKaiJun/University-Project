public abstract class Product {
	
	    private String prodName;   //product name
	    private double price;      //product price
	    private int qAvai;         //quantity available in stock
	    private int itemNum;       //item number of the product
	    private boolean prodStat;  //product status : active (true)

	    // Default constructor
	    public Product() {
	        prodStat = true; // default status is active
	    }

	    // Parameterized constructor
	    public Product(int itemNum, String prodName, int qAvai, double price, boolean prodStat) {
	        this.itemNum = itemNum;
	        this.prodName = prodName;
	        this.qAvai = qAvai;
	        this.price = price;
	        this.prodStat = prodStat;
	    }

	    // Getter and setter methods
	    public String getProdName() {
	        return prodName;
	    }

	    public void setProdName(String prodName) {
	        this.prodName = prodName;
	    }

	    public double getPrice() {
	        return price;
	    }

	    public void setPrice(double price) {
	        this.price = price;
	    }

	    public int getqAvai() {
	        return qAvai;
	    }

	    public void setqAvai(int qAvai) {
	        this.qAvai = qAvai;
	    }
	    
	    public int getItemNum() {
	        return itemNum;
	    }

	    public void setItemNum(int itemNum) {
	        this.itemNum = itemNum;
	    }

	    public boolean getProdStat() {
	        return prodStat;
	    }

	    public void setProdStat(boolean prodStat) {
	        this.prodStat = prodStat;
	    }

	    // Method to get total inventory value
	    public double getIntVal() {
	        return price * qAvai;
	    }

	    // Method to allow user to add quantity to stock
	    public void addStock(int quantity) {
	        if (prodStat) {
	            qAvai += quantity;
	        } 
	        else {
	            System.out.println("Sorry, cannot add stock to a discontinued product line.");
	        }
	    }

	    // Method to allow user to deduct quantity from stock
	    public void deductStock(int quantity) {
	            if (quantity <= qAvai) {
	                qAvai -= quantity;
	            } 
	            else {
	                System.out.println("Not enough stock available to deduct.");
	            }
	    }
	    
	   // Method to allow user to discontinue the product
	    public void discontinueProduct() {
	        prodStat = false;
	    }
	        

	    // Override toString method
	    @Override
	    public String toString() {
	        return "Item number: " + itemNum +
	               "\nProduct name: " + prodName +
	               "\nQuantity available: " + qAvai +
	               "\nPrice (RM): " + price +
	               "\nInventory value (RM): " + getIntVal() +
	               "\nProduct status: " + (prodStat ? "Active" : "Discontinued");
	    }
}


