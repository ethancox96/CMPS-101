//Ethan Cox
//etecox
//pa3
//Matrix.java
//Implements the MatrixADT Sparse.java will use

public class Matrix{
     //private class Entry
     //stores the column and value corresponding to a Matrix entry
     private class Entry {
         int col;
         int row;
         double entry;
            
         public Entry(int ro, int column, double ent){
             row = ro;
             col = column;
             entry = ent;
         }
         
         public boolean equals(Entry E){
             if (E.col == this.col && E.entry == this.entry)
                 return true;
             return false;
         }
         
         public String toString(){
             StringBuilder sb = new StringBuilder();
             sb.append("(").append(this.col+", ").append(this.entry + ")");
             return new String(sb);
         }
     }
     
     //public variables
     int size;
     int nnz;
     List[] list;
     
     // Makes a new n x n zero Matrix if n >= 1
     Matrix(int n){
         size = n;
         nnz = 0;
         if (n >= 1){
             list = new List[size+1];
         }
         //initialize Matrix
         for (int i = 1; i <= size; i++){
             list[i] = new List();
         }
     }
     
     //Access functions------------------------------------------------
     
     //int getSize()
     //returns the number of rows and columns in this Matrix
     int getSize(){
         return this.size;
     }
     
     //int getNNZ()
     //returns the number of non-zero entries in this matrix
     int getNNZ(){
         return nnz;
     }
     
     //public boolean equals
     //overrides Objects equals method
     public boolean equals(Object x){
         //check if x is a Matrix
         if (Matrix.class.isAssignableFrom(x.getClass())){
            Matrix M = (Matrix)x;
            //check if size of both Matrices is the same
            if (M.getSize() != this.getSize()){
                return false;
            }
            
            //Make sure each element is the same
            else{
                for (int i = 1; i <= size; i++){
                    M.list[i].moveFront();
                    for (this.list[i].moveFront(); this.list[i].index()>=0; this.list[i].moveNext()){
                        if (M.list[i].get() != this.list[i].get()){
                            return false;
                        }
                        M.list[i].moveNext();
                    }
                }
                return true;
            }
        }
        else{
            return false;
        }
     }
     
     //void makeZero()
     //sets the matrix to the zero state
     void makeZero(){
         nnz = 0;
         for (int i = 1; i <= getSize(); i++){
             list[i].clear();
         }
     }
     
     //Matrix copy()
     //returns a new Matrix having the same entries as this Matrix
     Matrix copy(){
         Matrix C = new Matrix(this.getSize());
         Entry entry;
         for (int i = 1; i <= this.getSize(); i++){
             for (this.list[i].moveFront(); this.list[i].index() >= 0; this.list[i].moveNext()){
                 entry = (Entry)this.list[i].get();
                 C.list[i].append(entry);
             }
         }
         C.nnz = this.nnz;
         return C;
     }
     
     // void changeEntry(int i, int j, double x)
     // changesith row, jth column of this Matrix to x
     // pre: 1<=i<=getSize(), 1<=j<=getSize()
     void changeEntry(int i, int j, double x){
         Entry E = new Entry(i, j, x);
         Entry entry;
         //check x is non-zero
         if (x != 0.0){
             if ((i >= 1 && i <= this.getSize()) && (j >= 1 && j <= this.getSize())){
                 //check if j is in the middle or front of the list
                 for (this.list[i].moveFront(); this.list[i].index() >= 0; this.list[i].moveNext()){
                     entry = (Entry)list[i].get();
                     int col = entry.col;
                     if (j < col){
                         list[i].insertBefore(E);
                         break;
                     }
                 }
                 //j is at the end of the list
                 if (list[i].index() == -1){
                     list[i].append(E);
                 }
             }
             this.nnz++;
         }
     }
     
     // Matrix scalarMult(double x)
     // returns a new Matrix thatis the scalar product of this Matrix with x
     Matrix scalarMult(double x){
         Matrix B = new Matrix(size);
         Entry entry, C;
         //iterate through the rows of this Matrix
         for (int i = 1; i <= size; i++){
             //iterate through the colums of this Matrix
             for (this.list[i].moveFront(); this.list[i].index() >= 0; this.list[i].moveNext()){
                 C = (Entry)list[i].get();
                 int col = C.col;
                 int row = C.row;
                 double ent = x*C.entry;
                 B.changeEntry(row, col, ent);
                 B.nnz++;
             }
         }
         return B;
     }
     
     // Matrix add(Matrix M)
     // returns a new Matrix that is the sum of this Matrix with M
     // pre: getSize()==M.getSize()
     Matrix add(Matrix M){
         Matrix N = new Matrix(size);
         if (this.getSize() == M.getSize()){
             Entry e1, e2, e3;
             int col1, col2;
             double ent1, ent2;
             
             if (this.equals(M)){
                 N = scalarMult(2);
             }
             else {
             //iterate through all rows
                 for (int i = 1; i <= size; i++){
                     //iterate through all the elements in both lists
                     this.list[i].moveFront();
                     M.list[i].moveFront();
                     
                     while (this.list[i].index() >= 0 && M.list[i].index() >= 0){
                         e1 = (Entry)this.list[i].get();
                         e2 = (Entry)M.list[i].get();
                         
                         //if both entry's columns are the same add together and enter into new Matrix
                         if (e1.col == e2.col){
                             double entry = e1.entry + e2.entry;
                             if (entry != 0){
                                 N.changeEntry(i, e1.col, entry);
                                 N.nnz++;
                             }
                             this.list[i].moveNext();
                             M.list[i].moveNext();
                         }
                         
                         //if M's col is less enter M's entry into new Matrix and increment N
                         else if (e2.col < e1.col){
                             N.changeEntry(i, e2.col, e2.entry);
                             N.nnz++;
                             M.list[i].moveNext();
                         }
                         
                         //if this col is less enter this entry into new Matrix and increment this list
                         else {
                             N.changeEntry(i, e1.col, e1.entry);
                             N.nnz++;
                             this.list[i].moveNext();
                         }
                     }
                     
                     //if there are still elements in M left go through them and add them to the list
                     if (M.list[i].index >= 0){
                         while (M.list[i].index() >= 0){
                             e2 = (Entry)M.list[i].get();
                             N.changeEntry(i, e2.col, e2.entry);
                             N.nnz++;
                             M.list[i].moveNext();
                         }
                     }
                     
                     //if there are still elements in this list go through them and add them to the list
                     if (this.list[i].index() >= 0){
                         while (this.list[i].index() >= 0){
                             e1 = (Entry)this.list[i].get();
                             N.changeEntry(i, e1.col, e1.entry);
                             N.nnz++;
                             this.list[i].moveNext();
                         }
                     }
                 }
             }
         }
         return N;
     }
     
     // Matrix sub(Matrix M)
     // returns a new Matrix that is the difference of this Matrix with M
     // pre: getSize()==M.getSize()
     Matrix sub(Matrix M){
         Matrix N = new Matrix(size);
         if (this.getSize() == M.getSize()){
             Entry e1, e2, e3;
             int col1, col2;
             double ent1, ent2;
             
             if (this.equals(M)){
                 N = N;
             }
             else {
             //iterate through all rows
                 for (int i = 1; i <= size; i++){
                     //iterate through all the elements in both lists
                     this.list[i].moveFront();
                     M.list[i].moveFront();
            
                     while (this.list[i].index() >= 0 && M.list[i].index() >= 0){
                         e1 = (Entry)this.list[i].get();
                         e2 = (Entry)M.list[i].get();
                         
                         //if both entries cols are the same subtract and change entry 
                         if (e1.col == e2.col){
                             double entry = e1.entry - e2.entry;
                             if (entry != 0){
                                 e3 = new Entry(i, e1.col, entry);
                                 N.list[i].append(e3);
                                 N.nnz++;
                             }
                             this.list[i].moveNext();
                             M.list[i].moveNext();
                         }
                         
                         //if M's col is less than this col place 0 - M's entry into new Matrix
                         else if (e2.col < e1.col){
                             N.changeEntry(i, e2.col, (0 - e2.entry));
                             N.nnz++;
                             M.list[i].moveNext();
                         }
                         
                         //if this col is less than M's col place this entry into new Matrix
                         else {
                             N.changeEntry(i, e1.col, e1.entry);
                             N.nnz++;
                             this.list[i].moveNext();
                         }
                     }
                     
                     //if there are still elements in M left go through them and add them to the list
                     if (M.list[i].index >= 0){
                         while (M.list[i].index() >= 0){
                             e2 = (Entry)M.list[i].get();
                             N.changeEntry(i, e2.col, (0 - e2.entry));
                             N.nnz++;
                             M.list[i].moveNext();
                         }
                     }
                     
                     //if there are still elements in this list go through them and add them to the list
                     if (this.list[i].index() >= 0){
                         while (this.list[i].index() >= 0){
                             e1 = (Entry)this.list[i].get();
                             N.changeEntry(i, e1.col, e1.entry);
                             N.nnz++;
                             this.list[i].moveNext();
                         }
                     }
                 }
             }
         }
         return N;
     }
     
     //Matrix transpose()
     // returns a new Matrix that is the transpose of this Matrix
     Matrix transpose(){
         Matrix T = new Matrix(this.getSize());
         Entry e1, entry;
         for (int i = 1; i <= this.getSize(); i++){
             for (this.list[i].moveFront(); this.list[i].index() >= 0; this.list[i].moveNext()){
                 e1 = (Entry)this.list[i].get();
                 T.changeEntry(e1.col, e1.row, e1.entry);
             }
         }
         return T;
     }
     
     // Matrix mult(Matrix M)
     // returns a new Matrix that is the product of this Matrix with M
     // pre: getSize()==M.getSize()
     Matrix mult(Matrix M){
         Matrix N = new Matrix(this.getSize());
         Matrix T = M.transpose();
         for (int i = 1; i <= this.getSize(); i++){
             for (int j = 1; j <= this.getSize(); j++){
                 double dot = dot(this.list[i], T.list[j]);
                 if (dot != 0){
                     N.changeEntry(i, j, dot);
                 }
             }
         }
         return N;
     }
     
     // public String toString()
     // overrides Objects toString() function
     public String toString(){
         StringBuilder sb = new StringBuilder();
         for (int i = 1; i <= size; i++){
             if (this.list[i].numItems > 0){
                 sb.append(i + ": ");
                 for (this.list[i].moveFront(); this.list[i].index() >= 0; this.list[i].moveNext()){
                     Entry entry = (Entry)this.list[i].get();
                     sb.append(entry.toString());
                 }
                 sb.append("\n");
             }
             
         }
         return new String(sb);
     }
     
     //Helper Functions---------------------------------------------------------------
     
     // private static double dot(List P, List Q)
     // computes the dot product for two rows
     private static double dot(List P, List Q){
         double total = 0.0;
         Entry e, e2, e3;
         //if both Lists are the same calculate dot
         if (P.equals(Q)){
             for (P.moveFront(); P.index() >= 0; P.moveNext()){
                 e = (Entry)P.get();
                 total += 2*e.entry;
             }
         }
         
         else{
             Q.moveFront();
             P.moveFront();
             //iterate while both lists are not at end
             //don't need to calculate any value if P or Q is 0
             while (P.index() >= 0 && Q.index() >= 0){
                 e = (Entry)P.get();
                 e2 = (Entry)Q.get();
                 if (e.col == e2.col){
                     total += e.entry * e2.entry;
                     P.moveNext();
                     Q.moveNext();
                 }
                 else if (e.col < e2.col){
                     P.moveNext();
                 }
                 else{
                     Q.moveNext();
                 }
             }
         }
         return total;
     }
     
}






