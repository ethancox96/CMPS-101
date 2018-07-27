//Ethan Cox
//etecox
//Sparse.java
//PA3
//Takes in input and runs the MatrixADT

import java.io.*;
import java.util.Scanner;

public class Sparse{
    public static void main(String[] args) throws IOException{
        //create variables to used
        int n, a, b,row, col;
        double ent;
        Scanner in;
        PrintWriter out = null;
        String line = null;
        String[] token = null;
        
        //check if number of args is correct
        if (args.length != 2){
            System.err.println("Usage: FileIO infile outfile");
            System.exit(1);
        }
        
        in = new Scanner(new File(args[0]));
        out = new PrintWriter(new FileWriter(args[1]));
        
        //get size of Matrices and number of entries in each
        line = in.nextLine() + " ";
        token = line.split("\\s+");
        n = Integer.parseInt(token[0]);
        a = Integer.parseInt(token[1]);
        b = Integer.parseInt(token[2]);
        
        //deal with blank line
        in.nextLine();
        //get entries and store them in Matrix A
        Matrix A = new Matrix(n);
        for (int i = 0; i < a; i++){
            line = in.nextLine();
            token = line.split("\\s+");
            row = Integer.parseInt(token[0]);
            col = Integer.parseInt(token[1]);
            ent = Double.parseDouble(token[2]);
            A.changeEntry(row, col, ent);
        }
        
        //deal with blank line
        in.nextLine();
        //get entries and store them in Matrix B
        Matrix B = new Matrix(n);
        for (int j = 1; j <= b; j++){
            line = in.nextLine();
            token = line.split("\\s+");
            row = Integer.parseInt(token[0]);
            col = Integer.parseInt(token[1]);
            ent = Double.parseDouble(token[2]);
            B.changeEntry(row, col, ent);
        }
        
        //print out Matrix A
        out.println("A has " + A.getNNZ() + " non-zero entries:");
        out.println(A);
        
        //print out Matrix B
        out.println("B has " + B.getNNZ() + " non-zero entries:");
        out.println(B);
        
        //print out 1.5 * A
        out.println("(1.5)*A =");
        Matrix C = A.scalarMult(1.5);
        out.println(C);
        
        //print out A+B
        out.println("A+B =");
        Matrix D = A.add(B);
        out.println(D);
        
        //print out A+A
        out.println("A+A =");
        Matrix E = A.add(A);
        out.println(E);
        
        //print out B - A
        out.println("B-A =");
        Matrix F = B.sub(A);
        out.println(F);
        
        //print out A-A
        out.println("A-A =");
        Matrix G = A.sub(A);
        out.println(G);
        
        //print out Transpose(A)
        out.println("Transpose(A) =");
        Matrix H = A.transpose();
        out.println(H);
        
        //print out A*B
        out.println("A*B =");
        Matrix J = A.mult(B);
        out.println(J);
        
        //print out B*B
        out.println("B*B =");
        Matrix K = B.mult(B);
        out.println(K);
        
        //close files
        in.close();
        out.close();
    }
}







