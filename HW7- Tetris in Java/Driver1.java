import java.util.Scanner;

public class Driver1 {
    public static void main(String[] args) {
        System.out.println("\t\t **********  DRIVER - 1   ************ \n\n");
	
        System.out.println("*************************** TESTING PRINT AND ROTATE FUNCTIONS OF TETROMINO CLASS ****************** \n\n");

        System.out.println("--------------- I Tetromino : ------------------- \n");
        Tetromino tI = new Tetromino(TetrominoType.I);
        System.out.println("Print I Tetromino : \n");
        tI.print();
        System.out.println("\nRotate right and print I Tetromino : \n");
        tI.rotate(DirectionType.Right);
        tI.print();
        System.out.println("\n");	

        System.out.println("--------------- O Tetromino : ------------------- \n");
        Tetromino tO = new Tetromino(TetrominoType.O);
        System.out.println("Print O Tetromino : \n");
        tO.print();
        System.out.println("\nRotate right and print O Tetromino : \n");
        tO.rotate(DirectionType.Right);
        tO.print();
        System.out.println("\n");


        System.out.println("--------------- T Tetromino : ------------------- \n");
        Tetromino tT = new Tetromino(TetrominoType.T);
        System.out.println("Print T Tetromino : \n");
        tT.print();
        System.out.println("\nRotate right and print T Tetromino : \n");
        tT.rotate(DirectionType.Right);
        tT.print();
        System.out.println("\n");
        System.out.println("\nRotate right and print T Tetromino : \n");
        tT.rotate(DirectionType.Right);
        tT.print();
        System.out.println("\n");
        System.out.println("\nRotate right and print T Tetromino : \n");
        tT.rotate(DirectionType.Right);
        tT.print();
        System.out.println("\n");
            
        System.out.println("--------------- J Tetromino : ------------------- \n");	
        Tetromino tJ = new Tetromino(TetrominoType.J);
        System.out.println("Print J Tetromino : \n");
        tJ.print();
        System.out.println("\nRotate right and print J Tetromino : \n");
        tJ.rotate(DirectionType.Right);
        tJ.print();
        System.out.println("\n");
        System.out.println("\nRotate right and print J Tetromino : \n");
        tJ.rotate(DirectionType.Right);
        tJ.print();
        System.out.println("\n");
        System.out.println("\nRotate right and print J Tetromino : \n");
        tJ.rotate(DirectionType.Right);
        tJ.print();
        System.out.println("\n");
        
        
        System.out.println("--------------- L Tetromino : ------------------- \n");
        Tetromino tL = new Tetromino(TetrominoType.L);
        System.out.println("Print L Tetromino : \n");
        tL.print();
        System.out.println("\nRotate right and print L Tetromino : \n");
        tL.rotate(DirectionType.Right);
        tL.print();
        System.out.println("\n");
        System.out.println("\nRotate right and print L Tetromino : \n");
        tL.rotate(DirectionType.Right);
        tL.print();
        System.out.println("\n");
        System.out.println("\nRotate right and print L Tetromino : \n");
        tL.rotate(DirectionType.Right);
        tL.print();
        System.out.println("\n");
        
        System.out.println("--------------- S Tetromino : ------------------- \n");
        Tetromino tS = new Tetromino(TetrominoType.S);
        System.out.println("Print T Tetromino : \n");
        tS.print();
        System.out.println("\nRotate right and print S Tetromino : \n");
        tS.rotate(DirectionType.Right);
        tS.print();
        System.out.println("\n");
        System.out.println("\nRotate right and print S Tetromino : \n");
        tS.rotate(DirectionType.Right);
        tS.print();
        System.out.println("\n");
        System.out.println("\nRotate right and print S Tetromino : \n");
        tS.rotate(DirectionType.Right);
        tS.print();
        System.out.println("\n");
        
        System.out.println("--------------- Z Tetromino : ------------------- \n");
        Tetromino tZ = new Tetromino(TetrominoType.Z);
        System.out.println("Print T Tetromino : \n");
        tZ.print();
        System.out.println("\nRotate right and print Z Tetromino : \n");
        tZ.rotate(DirectionType.Right);
        tZ.print();
        System.out.println("\n");
        System.out.println("\nRotate right and print Z Tetromino : \n");
        tZ.rotate(DirectionType.Right);
        tZ.print();
        System.out.println("\n");
        System.out.println("\nRotate right and print Z Tetromino : \n");
        tZ.rotate(DirectionType.Right);
        tZ.print();
        System.out.println("\n");
        

        System.out.println("\n*************************** TESTING DRAW FUNCTION OF TETRIS CLASS WHEN BOARD IS EMPTY ****************** \n\n");
        final int length = 10;
        final int width = 10;
        
        Tetris tetris = new Tetris(length, width);
        System.out.println("TETRIS BOARD LENGTH*WIDTH = " + length + "*" + width + "\n\n");
        
        tetris.draw();
        System.out.println("\n");
        
        
        System.out.println("\n*************************** TESTING ADD FUNCTION OF TETRIS CLASS ************************ \n\n");
        Tetromino newTet = new Tetromino(TetrominoType.I);
        
        System.out.println("New Tetromino : \n");
        newTet.print();
        System.out.println("\n");
        
        tetris.add(newTet);
        System.out.println("Tetris Board After Adding New Tetromino : \n");
        tetris.draw();
        System.out.println("\n");
        
        Tetris tetris2 = new Tetris(length, width);
        Tetromino newTet2 = new Tetromino(TetrominoType.Z);
        
        System.out.println("New Tetromino : \n");
        newTet2.print();
        System.out.println("\n");
        
        tetris2.add(newTet2);
        System.out.println("Tetris Board After Adding New Tetromino : \n");
        tetris2.draw();
        System.out.println("\n");
        
        System.out.println("\n*************************** TESTING PutRandom FUNCTION OF TETRIS CLASS - 2************************* \n\n");
        
        System.out.println("Added Tetromino : \n");
        newTet.print();
        System.out.println("\n");
        
        System.out.println("Tetris Board After A New Tetromino At The Top (It'll be dropped while animating): \n");
        tetris.putRandom();
        tetris.draw();
        System.out.println("\n");
        
        System.out.println("Added Tetromino : \n");
        newTet2.print();
        System.out.println("\n");
        
        System.out.println("Tetris Board After Fitting New Tetromino At The Top (It'll be dropped while animating): \n");
        tetris2.putRandom();
        tetris2.draw();
        System.out.println("\n\n");
        
        System.out.println("\n*************************** TESTING ANIMATE FUNCTION OF TETRIS CLASS ************************* \n\n");
        
        System.out.println("\n ******* ANIMATE TEST - 1 : ************ \n");
        System.out.println("Tetromino list will be sent to animate : L, S, T, Z, O, I, I, L, J, T, T, S, Z, I, J, J, L, J, I, S, Z, O \n");
        System.out.println("Press Any Character to Test Animate Function : ");
        Scanner scanner = new Scanner(System.in);
        scanner.nextLine();
        
        Tetris animateTetris = new Tetris(10, 10);
        Tetromino[] tetrominoList = new Tetromino[]{new Tetromino(TetrominoType.L), new Tetromino(TetrominoType.S), new Tetromino(TetrominoType.T), new Tetromino(TetrominoType.Z), new Tetromino(TetrominoType.O), new Tetromino(TetrominoType.I),
                    new Tetromino(TetrominoType.I), new Tetromino(TetrominoType.L), new Tetromino(TetrominoType.J), new Tetromino(TetrominoType.T), new Tetromino(TetrominoType.T), new Tetromino(TetrominoType.S),
                    new Tetromino(TetrominoType.Z), new Tetromino(TetrominoType.I), new Tetromino(TetrominoType.J), new Tetromino(TetrominoType.J), new Tetromino(TetrominoType.L), new Tetromino(TetrominoType.J),
                    new Tetromino(TetrominoType.I), new Tetromino(TetrominoType.S), new Tetromino(TetrominoType.Z), new Tetromino(TetrominoType.O)
        };
        
        boolean isDone = false;
        for (int i = 0; i < tetrominoList.length && !isDone; ++i) {
            
            Tetromino tet = tetrominoList[i];
            animateTetris.add(tet);
                
            if (animateTetris.gameStatus() == false) {
                System.out.println("\n ******* ANIMATE TEST - 1 : ************ \n");
        
                System.out.println("Current tetromino : \n");
                tet.print();
                System.out.println("\n");
                
                System.out.println("Current tetromino cannot be added at the top row in the middle !\n\n");
                
                System.out.println("The board : \n");
                animateTetris.draw();
            
                System.out.println("\nGAME OVER!\n");
                
                isDone = true;
            }
            
            else {
                animateTetris.animate();
            }	
        }
        
        
        System.out.println("\n ******* ANIMATE TEST - 2 : ************ \n");
        System.out.println("Tetromino list will be sent to animate : O, J, L, S, Z, T, L, J, S, O, T, Z, J, I, L, J, O, S \n");
        System.out.println("Press Any Character to Test Animate Function : ");
        scanner.nextLine();
        
        animateTetris = new Tetris(10, 8);
        Tetromino[] tetrominoList2 = new Tetromino[] {
                            new Tetromino(TetrominoType.O), new Tetromino(TetrominoType.J), new Tetromino(TetrominoType.L), new Tetromino(TetrominoType.S), new Tetromino(TetrominoType.Z), new Tetromino(TetrominoType.T),
                            new Tetromino(TetrominoType.L), new Tetromino(TetrominoType.J), new Tetromino(TetrominoType.S), new Tetromino(TetrominoType.O), new Tetromino(TetrominoType.T), new Tetromino(TetrominoType.Z),
                            new Tetromino(TetrominoType.J), new Tetromino(TetrominoType.I), new Tetromino(TetrominoType.L), new Tetromino(TetrominoType.J), new Tetromino(TetrominoType.O), new Tetromino(TetrominoType.S)
                        };
        
        isDone = false;
        for (int i = 0; i < tetrominoList2.length && !isDone; ++i) {
            
            Tetromino tet = tetrominoList2[i];
            animateTetris.add(tet);
                
            if (animateTetris.gameStatus() == false) {
                System.out.println("\n ******* ANIMATE TEST - 2 : ************ \n");
        
                System.out.println("Current tetromino : \n");
                tet.print();
                System.out.println("\n");
                
                System.out.println("Current tetromino cannot be added at the top row in the middle !\n\n");
                
                System.out.println("The board : \n");
                animateTetris.draw();
            
                System.out.println("\nGAME OVER!\n");
                
                isDone = true;
            }
            
            else {
                animateTetris.animate();
            }	
        }
        
        System.out.println("\n\n");
    
        scanner.close();
    }


}

