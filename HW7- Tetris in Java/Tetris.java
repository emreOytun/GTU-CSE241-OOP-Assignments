import java.util.Random;

/**
* <h1>Tetris Class</h1>
* Tetris class implements all needed functions to create the game tetris.
*
* @author Emre Oytun
*/
public class Tetris {
    private Map gameMap;
    private boolean status;

    private boolean isCurTetrominoActive;
	private Tetromino curTetromino;

    /**
     * Constructs the tetris with the given parameters.
     * @param rowNum
     * @param colNum
     */
    Tetris(int rowNum, int colNum) {
        this.gameMap = new Map(rowNum, colNum);
        this.status = true;
        this.isCurTetrominoActive = false;
    }

    /**
     * 1) Adjusts the new tetromino's position to be at the top row in the middle, and checks if it can be added to the map. <br>
	* 2) If it can be added then new tetromino is active for game; if it's not then the new tetromino is not active.
     * @param Tetromino - New tetromino to be added.
     */
    public void add(Tetromino newTetromino) {
        curTetromino = newTetromino;

        /* Set the position of the tetromino to the middle of the game map. */
        int gameMap_middle_col = (int) (gameMap.getColNum()/2);
        int curTetromino_startCol = gameMap_middle_col - (int) (curTetromino.getActiveColNum()/2);
        curTetromino.setStartPosition(0, curTetromino_startCol);
        
        if (!gameMap.canBeAdded(curTetromino)) {
            status = false;
            isCurTetrominoActive = false;
        }
        else isCurTetrominoActive = true;
    }

    /**
     * Puts the current tetromino to a random position.
     */
    public void putRandom() {

        if (isCurTetrominoActive) {
            boolean isDone = false;
            Random random = new Random();
            do {
                int randomCol = random.nextInt(gameMap.getColNum());
                randomCol = randomCol % gameMap.getColNum();
                if (randomCol + curTetromino.getActiveColNum() <= gameMap.getColNum()) {
                    curTetromino.setStartY(randomCol);
                    isDone = true;
                }

            }while (!isDone);
        }
        
    }

    /**
     * Draws the board with the current tetromino if there is an active current tetromino, or draws the board without a new tetromino otherwise.
     */
    public void draw() {
        System.out.println("-------------------------------------------");

        if (isCurTetrominoActive) {
            gameMap.addTetromino(curTetromino);
            gameMap.print();
            gameMap.deleteTetromino(curTetromino);
        }
        
        else {
            gameMap.print();
        }

    }

    /**
     * Animates the tetris game by lowering the current tetromino step-by-step.
     */
    public void animate()  {
        if (!isCurTetrominoActive) return;
    
        draw();
        putRandom();
        
        boolean isPlaced = false;
        while (!isPlaced) {
            /* Add the temporary tetromino to the map, draw the map, and delete it from the map. */
            draw();
            System.out.println();
            
            try {
                Thread.sleep(150);
            } catch (InterruptedException e) {
            
            }

            Tetromino copy = (Tetromino) curTetromino.clone();
			copy.lower();
			
			if (gameMap.canBeAdded(copy) == false) isPlaced = true;
			else {
				curTetromino.lower();
			}
        }
        
        /* Lastly, add the new tetromino to the board permanently. */
        gameMap.addTetromino(curTetromino);
    }
 	
    /**
     * 
     * @return Boolean - True if the game continues, false otherwise.
     */
    boolean gameStatus() { return status; }

}




/********************** MAP CLASS TO REPRESENT THE GAME BOARD. ******************************/

class Map implements Cloneable {

    private char[][] map;
    private int rowNum;
    private int colNum;

    /**
     * Constructs the map with the given row and column numbers.
     * @param rowNum
     * @param colNum
     */
    public Map(int rowNum, int colNum) {
        this.rowNum = rowNum;
        this.colNum = colNum;
        
        this.map = new char[rowNum][colNum];
        for (int i = 0; i < rowNum; ++i) {
            for (int j = 0; j < colNum; ++j) {
                map[i][j] = ' ';
            }
        }

    }

    /**
     * Clones the map.
     * @return Object - Cloned map.
     */
    @Override
    public Object clone() {
        try {
            Map copy = (Map) super.clone();

            copy.map = new char[rowNum][colNum];
            for (int i = 0; i < rowNum; ++i) {
                for (int j = 0; j < colNum; ++j) {
                    copy.map[i][j] = this.map[i][j];
                }
            }

            return copy;
        } catch (CloneNotSupportedException e) {
            e.getStackTrace();
        }
        return null;
    }

    /**
     * 
     * @return Int - Row number of the map.
     */
    public int getRowNum() {
        return rowNum;
    }

    /**
     * 
     * @return Int - Column number of the map.
     */
    public int getColNum() {
        return colNum;
    }

    /**
     * Prints the map.
     */
    public void print() {
        for (char[] line : map) {
            for (char ch : line) {
                if (ch == ' ') System.out.print("*");
                else System.out.print(ch);
            }      
            System.out.println();    
        }
    }

    /**
     * Add the coming active block with the given coordinates to the map.
     * @param Char[][] - Tetromino block to be added to the map.
     * @param Int - start_x 
     * @param Int - start_y
     */
    public void addActiveBlock(char[][] block, int start_x, int start_y) {
        for (int i = 0; i < block.length; ++i) {
            for (int j = 0; j < block[i].length; ++j) {
                if (block[i][j] != ' ') map[i+start_x][j+start_y] = block[i][j];
            }
        }
    }

    /**
     * It adds the given tetromino to the map.
     * @param Tetromino - New tetromino to be added.
     */
    public void addTetromino(Tetromino t) {
        char[][] block = t.getBlock();
        
        for (int i = 0; i < t.getActiveRowNum(); ++i) {
            for (int j = 0; j < t.getActiveColNum(); ++j) {
                if (block[i][j] != ' ') map[i+t.getStartX()][j+t.getStartY()] = block[i][j];
            }
        }
    }

    /**
     * It deletes the given tetromino from the map.
     * @param Tetromino - To be deleted from the map.
     */
    public void deleteTetromino(Tetromino t) {
        char[][] block = t.getBlock();
        
        for (int i = 0; i < t.getActiveRowNum(); ++i) {
            for (int j = 0; j < t.getActiveColNum(); ++j) {
                if (block[i][j] != ' ') map[i+t.getStartX()][j+t.getStartY()] = ' ';
            }
        }
        
    }

    /**
     * It checks if a given tetromino can be added to the map.
     * @param Tetromino - To be checked.
     * @return Boolean - True if it can be added, false otherwise.
     */
    public boolean canBeAdded(Tetromino t) {
        char[][] blocks = t.getBlock();
        
        int start_x = t.getStartX();
        int start_y= t.getStartY();
        
        boolean canAdded = true;
        for (int i = 0; i < t.getActiveRowNum() && canAdded; ++i) {
            for (int j = 0; j < t.getActiveColNum() && canAdded; ++j) {
                if (i+start_x<0 || i+start_x>=rowNum || j+start_y<0 || j+start_y>=colNum)	canAdded = false;

                if (i+start_x>=0 && i+start_x<rowNum && j+start_y>=0 && j+start_y<colNum && map[i+start_x][j+start_y] != ' ' && blocks[i][j] != ' ') canAdded = false; 		
            }
        }

        return canAdded;
    }

}

