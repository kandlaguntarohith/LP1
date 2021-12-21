import java.util.ArrayList;
import java.util.List;
import java.util.PriorityQueue;
import java.util.*;
import java.io.*;

public class Main {
	public int dimension = 3;

	int[] row = { 1, 0, -1, 0 };
	int[] col = { 0, -1, 0, 1 };

	int moves = 0;

	PriorityQueue<Node> pq = new PriorityQueue<Node>(1000, (a, b) -> (a.cost + a.level) - (b.cost + b.level));
	HashSet<Node> visited = new HashSet<>();

	public int calculateCost(int[][] initial, int[][] goal) {
		int count = 0;
		int n = initial.length;
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (initial[i][j] != 0 && initial[i][j] != goal[i][j]) {
					count++;
				}
			}
		}
		return count;
	}

	public void printMatrix(int[][] matrix) {
		for (int i = 0; i < matrix.length; i++) {
			for (int j = 0; j < matrix.length; j++) {
				System.out.print(matrix[i][j] + " ");
			}
			System.out.println();
		}
	}

	public boolean isSafe(int x, int y) {
		return (x >= 0 && x < dimension && y >= 0 && y < dimension);
	}

	public void printPath(Node root) {
		if (root == null) {
			return;
		}
		moves++;
		printPath(root.parent);
		if (root.parent != null) {
			System.out.println("  |");
			System.out.println("  V");
		}
		System.out.println();
		printMatrix(root.matrix);
		System.out.println();
	}

	// Function to check whether problem is solvable or not
	public boolean isSolvable(int[][] matrix) {
		int count = 0;
		List<Integer> array = new ArrayList<Integer>();

		for (int i = 0; i < matrix.length; i++) {
			for (int j = 0; j < matrix.length; j++) {
				array.add(matrix[i][j]);
			}
		}

		Integer[] anotherArray = new Integer[array.size()];
		array.toArray(anotherArray);

		for (int i = 0; i < anotherArray.length - 1; i++) {
			for (int j = i + 1; j < anotherArray.length; j++) {
				if (anotherArray[i] != 0 && anotherArray[j] != 0 && anotherArray[i] > anotherArray[j]) {
					count++;
				}
			}
		}

		return count % 2 == 0;
	}

	public void addToQueue(Node node) {
		if (!visited.contains(node))
			pq.add(node);
	}

	public void solvePuzzle(int[][] initial, int[][] goal, int x, int y) {
		Node root = new Node(initial, x, y, x, y, 0, null);
		root.cost = calculateCost(initial, goal);
		addToQueue(root);

		while (!pq.isEmpty()) {
			Node min = pq.poll();
			if (min.cost == 0) {
				printPath(min);

				System.out.println("Number of moves required to reach final matrix: " + --moves);
				return;
			}

			visited.add(min);

			for (int i = 0; i < 4; i++) {
				if (isSafe(min.x + row[i], min.y + col[i])) {
					Node child = new Node(min.matrix, min.x, min.y, min.x + row[i], min.y + col[i], min.level + 1, min);
					child.cost = calculateCost(child.matrix, goal);
					addToQueue(child);
				}
			}
		}

	}

	// intial position of the space/_
	public int[] findTilePosition(int initial[][]) {
		int res[] = new int[2];
		for (int i = 0; i < initial.length; i++) {
			for (int j = 0; j < initial[0].length; j++) {
				if (initial[i][j] == 0) {
					res[0] = i;
					res[1] = j;
				}
			}
		}
		return res;
	}

	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		
		// initializing the start and goal matrix
		int initial[][] = new int[3][3];
		int goal[][] = new int[3][3];

		System.out.println("Enter the Start State :");
		for (int i = 0; i < initial.length; i++) {
			for (int j = 0; j < initial[0].length; j++) {
				initial[i][j] = scanner.nextInt();
			}
		}

		System.out.println("Enter the Goal State :");
		for (int i = 0; i < initial.length; i++) {
			for (int j = 0; j < initial[0].length; j++) {
				goal[i][j] = scanner.nextInt();
			}
		}

		System.out.println();

		// initializing the puzzle
		Main puzzle = new Main();

		int res[] = puzzle.findTilePosition(initial);

		if (puzzle.isSolvable(initial)) {
			puzzle.solvePuzzle(initial, goal, res[0], res[1]);

		} else {
			System.out.println("The given problem is unsolvable!!");
		}
	}
}



/**
 * Test Cases
 * 
 * 1) Initial state:
 * 1 2 3
 * _ 4 6
 * 7 5 8
 * 
 * Goal state:
 * 1 2 3
 * 4 5 6
 * 7 8 _
 * 
 * 2) Initial state:
 * 8 1 2
 * _ 4 3
 * 7 6 5
 * 
 * Goal state:
 * 1 2 3
 * 4 5 6
 * 7 8 _
 */