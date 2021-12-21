import java.util.*;
import java.io.*;

public class Node {
	public Node parent;
	public int[][] matrix;
	public int x, y;
	public int cost;
	public int level;

	public Node(int[][] matrix, int x, int y, int newX, int newY, int level, Node parent) {
		this.parent = parent;
		this.matrix = new int[matrix.length][];
		for (int i = 0; i < matrix.length; i++) {
			this.matrix[i] = matrix[i].clone();
		}

		int temp = this.matrix[x][y];
		this.matrix[x][y] = this.matrix[newX][newY];
		this.matrix[newX][newY] = temp;

		this.cost = Integer.MAX_VALUE;
		this.level = level;
		this.x = newX;
		this.y = newY;
	}

	public boolean equals(Object o) {
		if (this == o)
			return true;
		Node node = (Node) o;
		return Arrays.equals(matrix, node.matrix);
	}

	public int hashCode() {
		return Arrays.hashCode(matrix);
	}
}