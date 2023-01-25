import java.util.Random;
import java.util.Scanner;

public class Driver2 {
    
    public static Tetromino randomTetromino() {
        TetrominoType[] typeList = new TetrominoType[] {TetrominoType.I, TetrominoType.O, TetrominoType.L, TetrominoType.S, TetrominoType.Z, TetrominoType.J, TetrominoType.T};
        
        Random random = new Random();
        int randomNum = random.nextInt(7);
        randomNum = randomNum % 7; 

        return new Tetromino(typeList[randomNum]);
    }
    

    public static void main(String[] args) {
        System.out.println("\t\t ********* DRIVER - 2 ******** \n\n");
	
        int len = 0;
        int width = 0;
        
        Scanner scanner = new Scanner(System.in);
        
        /* Get the length of board. */
        boolean isRead = false;
        do {
            len = -1;
            System.out.println("Enter board length : ");
            
            /* Check the validity of the input. */
            if (!scanner.hasNextInt()) {
                System.out.println("Enter a valid input!");
                scanner.nextLine();
            }
            else {
                len = scanner.nextInt();
                if (len<0) System.out.println("Enter a positive number!");
                else isRead = true;
            }
        
        }while (!isRead);
        
        /* Get the width of board. */
        isRead = false;
        do {
            width = -1;
            System.out.println("Enter board width : ");
        
            /* Check the validity of the input. */
            if (!scanner.hasNextInt()) {
                System.out.println("Enter a valid input!");
                scanner.nextLine();
            }
            else {
                width = scanner.nextInt();
                if (width<0) System.out.println("Enter a positive number!");
                else isRead = true;
            }
    
        }while (!isRead);
        
        /* Initialize a Tetris instance with given board parameters. */
        Tetris tetris = new Tetris(len, width);
        
        scanner.nextLine();
        boolean isDone = false;
        while(!isDone) {
            isRead = true;
            char ch;
            System.out.println("Enter a tetromino (R - Random, 'T','O','L','S','J','Z','S', Q - Quit): ");
            
            String nextLine = scanner.nextLine();
            if (nextLine.length() == 0) {
                ch = 'E'; // 'E' for empty.
            }
            else {
                ch = nextLine.charAt(0);
            }
            Tetromino newT = null;
            
            switch (ch) {
                
                    case 'I' :
                    case 'i' :
                        newT = new Tetromino(TetrominoType.I);
                        break;
                    
                    case 'O' :
                    case 'o' :
                        newT = new Tetromino(TetrominoType.O);
                        break;
                        
                    case 'T' :
                    case 't' :
                        newT = new Tetromino(TetrominoType.T);  
                        break;
                        
                    case 'J' :
                    case 'j' :
                        newT = new Tetromino(TetrominoType.J);
                        break;
                    
                    case 'L' :
                    case 'l' :
                        newT = new Tetromino(TetrominoType.L);
                        break;
                        
                    case 'Z' :
                    case 'z' :
                        newT = new Tetromino(TetrominoType.Z);
                        break;
                        
                    case 'S' :
                    case 's' :
                        newT = new Tetromino(TetrominoType.S);
                        break; 	
                    
                    case 'R' :
                    case 'r' :
                        newT = randomTetromino();    
                        break;
                    
                    case 'Q':
                    case 'q':
                        System.out.println("Program is closing... Goodbye!");
                        isRead = false;
                        isDone = true;
                        break;

                    default :
                        System.out.println("Enter a valid input!\n");
                        isRead = false;
                        break;
                    
                }
                
                if (isRead) {
                    Tetromino curTet = newT;
                    
                    tetris.add(curTet);
                    
                    if (tetris.gameStatus() == false) {
                        System.out.println("Current tetromino : \n");
                        curTet.print();
                        System.out.println("\n");
                        
                        System.out.println("Current tetromino cannot be added at the top row in the middle !\n\n");
                        
                        System.out.println("The board : \n");
                        tetris.draw();
                    
                        System.out.println("\nGAME OVER!\n");
                        
                        isDone = true;
                    }
                    
                    else {
                        tetris.animate();
                    }
                    
                    System.out.println("\n");	
                }
        
        }
  
        scanner.close();
    }

}

