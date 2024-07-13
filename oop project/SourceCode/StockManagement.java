import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.InputMismatchException;
import java.util.Scanner;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.VBox;
import javafx.scene.text.Font;
import javafx.scene.text.Text;
import javafx.stage.Stage;

public class StockManagement extends Application {
    static public int number_added = 0; //global variable storing number of products added into product array
    private static final int FONT_SIZE = 20;
    
    public static int productToUpdate(Product[] product, Scanner scanner) { //method to list products so users can select one to update
	    System.out.println("\nProducts List:");
	    for (int i = 0; i < number_added; i++) {
	        System.out.println(i + ": " + product[i].getProdName());
	    }
	    System.out.print("Please select the product to update (enter index number): ");
	    int choice;
	    while (true) //loops infinitely until a valid input is entered
	    {
	    		try //Throws InputMismatchException if incorrect data type is entered
	    		{
	    			choice = scanner.nextInt();
	    			while (choice < 0 || choice >= number_added) { //prompts user to enter number again if the number entered is not within the valid indexes of the array
	    		        System.out.print("Invalid index number. Please select a valid index number: ");
	    		        choice = scanner.nextInt();
	    		    }
	    			break; //exits the infinite while loop when a valid input is entered
	    		}
	    		catch (InputMismatchException ex)
	    		{
	    			scanner.next(); //consumes invalid input
	    			System.out.print("Invalid input. Please select a valid index number: ");
	    		}
	    }
	    scanner.nextLine(); // consume the newline character
	    return choice; //returns the index of the product to update
	}

	public static void addStock(Product[] product, Scanner scanner) //method to add stocks to a particular product
	{
	    int to_update = productToUpdate(product, scanner); //grab product index to update from the productToUpdate method
	    System.out.print("Please enter the quantity to add: ");
	    int quantity;
	    try //Throws InputMismatchException if incorrect data type is entered
	    {
	    	quantity = scanner.nextInt();
	    }
	    catch (InputMismatchException ex)// If an invalid data type is entered, an error message will be displayed before the method is forcefully exited
	    {
	    	scanner.next(); //consumes invalid input
	    	System.out.println("Invalid data entered! Only numbers are accepted!\n");
	    	return;
	    }
	    while (quantity < 0) //Prompts user to enter quantity again if they enter a negative value
	    {
	        System.out.print("Invalid quantity. Please enter a positive value: ");
	        quantity = scanner.nextInt();
	    }
	    product[to_update].addStock(quantity);
	}

	public static void deductStock(Product[] product, Scanner scanner) //method to deduct stocks from a particular product
	{
	    int to_update = productToUpdate(product, scanner); //grab product index to update from the productToUpdate method
	    System.out.print("Please enter quantity to deduct: ");
	    int quantity;
	    try //Throws InputMismatchException if incorrect data type is entered
	    {
	    	quantity = scanner.nextInt();
	    }
	    catch (InputMismatchException ex) // If an invalid data type is entered, an error message will be displayed before the method is forcefully exited
	    {
	    	scanner.next(); //consumes invalid input
	    	quantity = 0;
	    	System.out.println("Invalid data entered! Only numbers are accepted!/n");
	    	return;
	    }
	    while (quantity < 0 || quantity > product[to_update].getqAvai()) // Prompts user to enter quantity again if they enter a negative value or a quantity value > current stocks
	    {
	    	if (quantity < 0)
	    	{
	    		System.out.print("Invalid quantity.\nPlease enter a positive value: ");
		        quantity = scanner.nextInt();
	    	}
	    	
	    	else
	    	{
	    		System.out.print("Failed! Cannot deduct more than stock availability.\nPlease enter a valid quantity: ");
		        quantity = scanner.nextInt();
	    	}
	    }
	    product[to_update].deductStock(quantity);
	}
	
	public static void addProduct(Product[] products, Scanner input) {
	    System.out.println("\nChoose a product to add\n1. Refrigerator\n2. TV\n3. Air Conditioner");
	    System.out.print("Enter selection: ");
	    int choice = getInputChoice(input, 3);
	    switch (choice) {
	        case 1:
	            addRefrigerator(products, input);
	            break;
	        case 2:
	            addTV(products, input);
	            break;
	        case 3:
	            addAirCond(products, input);
	            break;
	    }
	}
	
	// Utility method to handle choice input safely
	public static int getInputChoice(Scanner scanner, int maxOption) {
	    int choice;
	    while (true) {
	        try {
	            choice = scanner.nextInt();
	            if (choice >= 1 && choice <= maxOption) {
	                break;
	            }
	            System.out.println("Invalid choice. Please enter a number between 1 and " + maxOption + ".");
	        } catch (InputMismatchException ex) {
	            System.out.println("Invalid input. Please enter a numerical value.");
	            scanner.next();  // Consume the erroneous input
	        }
	    }
	    return choice;
	}
	
	public static void addRefrigerator(Product[] products, Scanner input) //method to add Refrigerator object into product array
	{
	    input.nextLine(); // clear input buffer
	    System.out.print("\nEnter product name: "); //create local variables to be inserted into Refrigerator object
	    String name = input.nextLine();
	    
	    System.out.print("Enter door design: ");
	    String design = input.nextLine();
	    
	    System.out.print("Enter color: ");
	    String color = input.nextLine();
	    
	    System.out.print("Enter capacity: ");
	    int capacity = input.nextInt();
	    
	    System.out.print("Enter quantity available in stock: ");
	    int stock = input.nextInt();
	    
	    System.out.print("Enter price: ");
	    double price = input.nextDouble();
	    
	    System.out.print("Enter item number: ");
	    int id = input.nextInt();
	    
	    // create Refrigerator object using user input and add to products array
	    products[number_added] = new Refrigerator(id, name, stock, price, true, design, color, capacity);
	    number_added++; //increment global variable by 1

	    System.out.println("Refrigerator " + name + " with item number " + id + " has been added.");
	}
	
	public static void addTV(Product[] products, Scanner input)
	{
		input.nextLine(); //clear input buffer
		 System.out.print("\nEnter product name: "); //create local variables to be inserted into TV object
		 String name = input.nextLine();
		 
		 System.out.print("Enter screen type: ");
		 String screenType = input.nextLine();
		 
		 System.out.print("Enter resolution: ");
		 String resolution = input.nextLine();
		 
		 System.out.print("Enter display size: ");
		 double displaySize = input.nextDouble();
		 
		 System.out.print("Enter quantity available in stock: ");
		 int stock = input.nextInt();
		 
		 System.out.print("Enter price: ");
		 double price = input.nextDouble();
		    
		 System.out.print("Enter item number: ");
		 int id = input.nextInt();
		 
		 
		 products[number_added] = new TV(id, name, stock, price, true, screenType, resolution, displaySize);
		 number_added++; //increment global variable by 1
		 
		 System.out.println("TV " + name + " with item number " + id + " has been added.");	
	}
	
	public static void addAirCond(Product[] products, Scanner input) 
	{
	    input.nextLine();  // Clear the buffer
	    System.out.print("\nEnter product name: ");
	    String name = input.nextLine();
	    
	    System.out.print("Enter horse power: ");
	    double hp = input.nextDouble();
	    
	    System.out.print("Enter refrigerant type: ");
	    input.nextLine();  // Clear the buffer
	    String refType = input.nextLine();
	    
	    System.out.print("Enter voltage: ");
	    double voltage = input.nextDouble();
	    
	    System.out.print("Enter quantity available in stock: ");
	    int stock = input.nextInt();
	    
	    System.out.print("Enter price: ");
	    double price = input.nextDouble();
	    
	    System.out.print("Enter item number: ");
	    int id = input.nextInt();

	    products[number_added] = new AirCond(id, name, stock, price, true, hp, refType, voltage);
	    number_added++;

	    System.out.println("Air Conditioner " + name + " with item number " + id + " has been added.");
	}
	
    public static int numberToAdd(Scanner in) //method to prompt user the maximum number of the products they want to add
	{
		int num;
		System.out.print("\nWhat is the maximum number of products you want to add?: ");
		do
		{
			try //Throws InputMismatchException if incorrect data type is entered
			{
				num = in.nextInt();
			}
			catch (InputMismatchException ex) //num = -1 if an invalid data type is entered
			{
				in.next(); //consumes invalid input
				num = -1;
			}
			if (num < 0)  //prompts user to enter number again if it is not 0 or above
				System.out.print("Invalid input! Please enter a number of 0 and above: ");
		}while (num <0);
		return(num);
	}
    
    public static void discontinueProduct(Product[] products, Scanner in) //method to discontinue a stock in the product array
	{
		int to_update;
		to_update = productToUpdate(products, in); //grab product index to update from the productToUpdate method
		products[to_update].setProdStat(false); //set status of the selected product to false
		System.out.println("Successfully discontinued " + products[to_update].getProdName() + "\n");
	}
    
    public static void main(String[] args) {
        launch(args);
    }
    
    @Override
    public void start(Stage primaryStage) {
        VBox root = new VBox(10);
        root.setAlignment(Pos.CENTER);
        root.setStyle("-fx-background-color: yellow;");// Set the background color to yellow

        // Welcome text at the top with larger font
        Text welcomeText = new Text("Welcome to Stock Management System");
        welcomeText.setFont(new Font(FONT_SIZE));

        // Current date and time with larger font
        SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy HH:mm:ss");
        Date date = new Date();
        Text dateTimeText = new Text(dateFormat.format(date));
        dateTimeText.setFont(new Font(FONT_SIZE));

        // Group members in the middle with larger font
        Text groupMembersText = new Text(
            "Group Members:\nHo Kah Mun\nLer Jun Wei\nLoh Wei Jia\nTan Kai Jun"
        );
        groupMembersText.setFont(new Font(FONT_SIZE));

        // Button at the bottom with larger font
        Button continueButton = new Button("Continue");
        continueButton.setFont(new Font(FONT_SIZE));
        continueButton.setOnAction(e -> primaryStage.close());

        // Add all components to the VBox
        root.getChildren().addAll(welcomeText, dateTimeText, groupMembersText, continueButton);

        Scene scene = new Scene(root, 900, 600); // Set the scene size

        primaryStage.setTitle("Stock Management System");
        primaryStage.setScene(scene);
        primaryStage.setOnHidden(e -> Platform.runLater(()->continueInConsole()));
        primaryStage.show();
    }

    
    public static void continueInConsole() {
        
    	System.out.println("Welcome to Stock Management System");
		SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy HH:mm:ss"); //create an object to indicate date format
		Date date = new Date(); //create a date object
		System.out.println(dateFormat.format(date) + "\n"); //display date as indicated by date format
		
		System.out.println("Group Members:");
		System.out.println("Ho Kah Mun");
		System.out.println("Ler Jun Wei");
		System.out.println("Loh Wei Jia");
		System.out.println("Tan Kai Jun\n");
    	
        UserInfo user = new UserInfo();
        Scanner input = new Scanner(System.in);
        
        System.out.println("Enter your full name (first name and surname): ");
        String fullName = input.nextLine(); 
		user.setName(fullName);// Pass the full name to setName() method
		user.setID(user.getName(), user.checkSpace(user.getName()));
		
		Product[] products = new Product[numberToAdd(input)]; //specify array size
		for(int i = 0; i < products.length; i++) //loop to add products into product array
		{
			int check;
			addProduct(products, input);
			if (i == (products.length - 1))
				System.out.println("Maximum number of products added.\n");
			else
			{
				System.out.print("Continue to add product? (1 - yes, 0 - no): "); //exit loop early if user doesn't want to add more product objects
				do
				{
					try //Throws InputMismatchException if incorrect data type is entered
					{
						check = input.nextInt();
					}
					catch (InputMismatchException ex) //num = -1 if an invalid data type is entered
					{
						input.next(); //consumes invalid input
						check = -1;
					}
					if (check < 0 || check > 1) //Prompts user to enter again if check is not 1 or 0
					{
						System.out.print("Invalid input! Please enter 1 or 0 (1 - yes, 0 - no): ");
						check = input.nextInt();
					}
					
				}while(check < 0 || check > 1);
				
				if (check == 0)
				{
					System.out.println();
					break;
				}
			}
		}
		
		menuSelect(menu(input), products, input); //displays menu and prompts user to make selection
		
		System.out.println("\nExited program.");
		System.out.println("User ID: " + user.getID());
		System.out.println("Username: " + user.getName());
		input.close();
        
    }
    
    
    public static void displayContent(Product[] products, Scanner input) //method to display information about all products in product array
    {
    	int option;
    	
    	for (int i = 0; i < number_added; i++)
    		System.out.println(products[i].toString());
    	do
    	{
    		System.out.println("\n1. Add Product");
    		System.out.println("2. Update Product");
    		System.out.println("3. Delete Product");
    		System.out.println("0. Back to Main Menu");
    	
    		try
    		{
    			option = input.nextInt();
    		}
    		catch(InputMismatchException ex)
    		{
    			input.next();
    			option = -1;
    		}
    	
    		switch(option)
    		
    		{
    		case 0:
    			return;
    		case 1:
    			addProduct(products, input);
    		case 2:
    			updateProduct(products, input);
    		case 3:
    			deleteProduct(products, input);
    		default:
				System.out.println("Invalid input! Please enter a number from 0 to 3!"); //prompts user to enter number again if the number entered is not between 0 and 3
    		}
    		
    	}while(option < 0 || option > 3);
    	
    }
    
    public static void updateProduct(Product[] products, Scanner input)
    {
    	input.nextLine();
    	int to_update = productToUpdate(products, input);
    	Product updateProd = products[to_update];
    	
    	System.out.println("Press enter if nothing to edit in that field.");
    	
    	System.out.println("Enter new item number: ");
        String newItemNum = input.nextLine();
        if (!newItemNum.isEmpty()) {
            updateProd.setItemNum(Integer.parseInt(newItemNum));
        }

        // Update product name
        System.out.println("Enter new product name: ");
        String newProdName = input.nextLine();
        if (!newProdName.isEmpty()) {
            updateProd.setProdName(newProdName);
        }

        // Update quantity available
        System.out.println("Enter new quantity available: ");
        String newQAvai = input.nextLine();
        if (!newQAvai.isEmpty()) {
            updateProd.setqAvai(Integer.parseInt(newQAvai));
        }

        // Update price
        System.out.println("Enter new price: ");
        String newPrice = input.nextLine();
        if (!newPrice.isEmpty()) {
            updateProd.setPrice(Double.parseDouble(newPrice));
        }

        // Update product status
        System.out.println("Enter new product status (true/false): ");
        String newProdStat = input.nextLine();
        if (!newProdStat.isEmpty()) {
            updateProd.setProdStat(Boolean.parseBoolean(newProdStat));
        }

        // Update specific fields for subclass (Refrigerator, TV, AirCond) if necessary
        if (updateProd instanceof Refrigerator) 
        {
            Refrigerator updateRefrigerator = (Refrigerator) updateProd;

            System.out.println("Enter new refrigerator door design: ");
            String newRefDoorDesg = input.nextLine();
            if (!newRefDoorDesg.isEmpty()) 
            {
            	updateRefrigerator.setRefDoorDesg(newRefDoorDesg);
            }
            
            System.out.println("Enter new refrigerator color: ");
            String newRefColor = input.nextLine();
            if (!newRefColor.isEmpty()) 
            {
            	updateRefrigerator.setRefColor(newRefColor);
            }

            System.out.println("Enter new refrigerator capacity: ");
            String newRefCap = input.nextLine();
            if (!newRefCap.isEmpty()) 
            {
            	updateRefrigerator.setRefCap(Double.parseDouble(newRefCap));
            }
            
        }
        else if (updateProd instanceof TV) 
        {
            TV updateTV = (TV) updateProd;

            System.out.println("Enter new TV screen type: ");
            String newTvScrTyp = input.nextLine();
            if (!newTvScrTyp.isEmpty()) 
            {
            	updateTV.setTvScrTyp(newTvScrTyp);
            }

            System.out.println("Enter new TV resolution: ");
            String newTvRes = input.nextLine();
            if (!newTvRes.isEmpty()) 
            {
            	updateTV.setTvRes(newTvRes);
            }
            
            System.out.println("Enter new TV display size: ");
            String newTvDisSize = input.nextLine();
            if (!newTvDisSize.isEmpty()) 
            {
            	updateTV.setTvDisSize(Double.parseDouble(newTvDisSize));
            }
        } 
        else if (updateProd instanceof AirCond) 
        {
            AirCond updateAirCond = (AirCond) updateProd;

            System.out.println("Enter new Air Conditioner horsepower: ");
            String newAcHP = input.nextLine();
            if (!newAcHP.isEmpty()) 
            {
            	updateAirCond.setAcHP(Double.parseDouble(newAcHP));
            }
            
            System.out.println("Enter new Air Conditioner horsepower: ");
            String newAcRefType = input.nextLine();
            if (!newAcRefType.isEmpty()) 
            {
            	updateAirCond.setAcHP(Double.parseDouble(newAcRefType));
            }
            
            System.out.println("Enter new Air Conditioner horsepower: ");
            String newAcVol = input.nextLine();
            if (!newAcVol.isEmpty()) 
            {
            	updateAirCond.setAcHP(Double.parseDouble(newAcVol));
            }

        }

    }
    
    public static void deleteProduct(Product[] products, Scanner input)
    {
    	int to_delete = productToUpdate(products, input);
    	String deletedName = products[to_delete].getProdName();

    	for (int i = to_delete; i < products.length - 1; i++) 
    	{
            products[i] = products[i + 1];
        }
    	
    	System.out.println("Product with the name " + deletedName + " has been deleted successfullly.");
    }
    
    public static int menu(Scanner scanner) { //Displays a menu for users to execute other methods from
        int choice;
        do {
            System.out.println("1. View products");
            System.out.println("2. Add stock");
            System.out.println("3. Deduct stock");
            System.out.println("4. Discontinue product");
            System.out.println("0. Exit");
            System.out.print("Please enter a menu option: ");
            try //Throws InputMismatchException if incorrect data type is entered
            {
            	choice = scanner.nextInt();
            }
            catch (InputMismatchException ex) //choice = -1 if an invalid data type is entered
            {
            	scanner.next(); //consumes invalid input
            	choice = -1;
            }
            if (choice < 0 || choice > 4)
            	System.out.println("Invalid input! Please enter a number from 0 to 4!"); //prompts user to enter number again if the number entered is not between 0 and 4
        } while (choice < 0 || choice > 4);
        return choice; //returns selection
    }
    
    public static void menuSelect(int menu, Product[] products, Scanner in) //method to execute method based on input from menu method
    {
    	do {
            switch (menu) { //switch...case statement to execute methods based on input in menu method
            
                case 1:
                	if (products.length == 0)
                		System.out.println("There are no products to display!\n");
                	else
                		displayContent(products, in);
                    menu = menu(in);
                    break;
                    
                case 2:
                	if (products.length == 0)
                		System.out.println("There are no products to update!\n");
                	else
                		addStock(products, in);
                    menu = menu(in);
                    break;
                    
                case 3:
                	if (products.length == 0)
                		System.out.println("There are no products to update!\n");
                	else
                		deductStock(products, in);
                    menu = menu(in);
                    break;
                    
                case 4:
                	if (products.length == 0)
                		System.out.println("There are no products to update!\n");
                	else
                		discontinueProduct(products, in);
                    menu = menu(in);
                    break;
                    
                case 0:
                    System.out.println("Exiting...");
                    break;
                    
            }
        } while (menu != 0); //Loops the method until 0 is input
    }
}