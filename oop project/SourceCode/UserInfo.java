import java.util.Scanner;

public class UserInfo {

	    private String name;
	    private String userId;

	    public UserInfo() {
	        this.name = "";
	        this.userId = "guest";
	    }

	    public void setName(String name) {
	        this.name = name;
	    }

	    public String getName() {
	        return name;
	    }

	    public String getID() {
	        return userId;
	    }
	    
	    public void setID(String name, boolean space){
            if(space){
                String[] nameParts = name.split(" ");
                String firstName = nameParts[0];
                String lastName = nameParts[nameParts.length - 1];
                char firstInitial = firstName.charAt(0);
                userId = Character.toUpperCase(firstInitial) + lastName;
            }
        }

	    public boolean checkSpace(String name) {
	        return name.contains(" ");
	    }

	    public static void main(String[] args) {
	        Scanner scanner = new Scanner(System.in);
	        UserInfo userInfo = new UserInfo();

	        System.out.println("Enter your full name (first name and surname):");
	        String fullName = scanner.nextLine();
	        userInfo.setName(fullName);

	        userInfo.setID(userInfo.getName(), userInfo.checkSpace(userInfo.getName()));

            if(userInfo.checkSpace(userInfo.getName())){
                System.out.println("User ID generated: " + userInfo.getID());
            }
            else{
                System.out.println("Invalid name format. User ID set to default: " + userInfo.getID());
            }

	        scanner.close();
	    }
	}

