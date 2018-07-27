//Ethan Cox
//etecox
//pa1
//Lex.java
//Orders the list lexicographically and prints it out

import java.io.*;
import java.util.Scanner;

class Lex{
    public static void main(String[] args) throws IOException{
        Scanner in = null;
        Scanner in2 = null;
        PrintWriter out = null;
        String line = null;
        String[] token = null;
        int i, n = 0, lineNumber = 0;
        
        if (args.length < 2){
            System.err.println("Usage: FileIO infile outfile");
            System.exit(1);
        }
        
        in = new Scanner(new File(args[0]));
        out = new PrintWriter(new FileWriter(args[1]));
        
        while( in.hasNextLine() ){
            n++;
            in.nextLine();
        }

        String[] list = new String[n];
	n = 0;
        in2 = new Scanner(new File(args[0]));
        while (in2.hasNextLine()){
            list[n] = in2.nextLine();
	    n++;
        }

        List A = new List();
        for (int j = 1; j <= n; j++)
            A.append(j);

        List B = new List();
        
        for(A.moveFront(); A.index()>=0; A.moveNext()){
            int key = A.get();
            if (B.length() == 0)
                B.prepend(key);
            else{
                B.moveFront();
                String s1 = list[key-1];
                String s2 = list[B.get()-1];
                while(s1.compareTo(s2) >= 0 && B.index > -1){
                    B.moveNext();
                    if (B.index() != -1)
                        s2 = list[B.get()-1];
                }
                if(B.index() == -1)
                    B.append(key);
                else
                    B.insertBefore(key);
            }
        }
        out.println(B.toString());
	in.close();
	out.close();
    }
}




