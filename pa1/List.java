//Ethan Cox
//etecox
//pa1
//List.java
//Implements the ListADT

public class List
{
    //private Node class
    private class Node{
        int item;
        //int index;
        Node next;
        Node prev;

        public Node(int h){
            item = h;
            //index = -1;
            next = prev = null;
        }
    }

    //local variables
    Node head;
    Node tail;
    Node cursor;
    int index;
    int numItems;

    //constructor for the list
    public List(){
        head = null;
        tail = null;
        cursor = null;
        numItems = 0;
    }
    
    //Acess functions
    //returns the number of elements in this list
    int length(){
        numItems = numItems - 1;
        return numItems + 1;
    }

    //If cursor is defined, returns the index of the cursor element,otherwise returns -1.
    int index(){
        if (cursor != null)
            return index;
        else
            return -1;
    }

    //returns the front element.  Pre: length() > 0
    int front(){
        if (this.length() > 0)
            return head.item;
        else
            return -1;
    }

    //returns the back element. Pre: length() > 0
    int back(){
        if (this.length() > 0)
            return tail.item;
        else
            return -1;
    }

    //returns cursor element.  Pre: length() > 0, index()>=0
    int get(){
        if (this.length() > 0 && this.index() >= 0){
            return cursor.item;
        }
        else
            return -1;
    }

    //returns if this List and L are the same integer sequence ignoring cursor
    boolean equals(List L){
        if ( L.numItems != this.numItems)
            return false;

        else{
            Node N = L.head;
            Node M = this.head;
            for (int i = 1; i <= numItems; i++){
                if (N.item != M.item)
                    return false;
            }
        }
        return true;
    }

    //Manipulation procedures
    //Resets this list to its original empty state
    void clear(){
        head = null;
        tail = null;
        cursor = null;
        index =
        numItems = 0;
    }

    //If List is non-empty, places the cursor under the front element, otherwisedoes nothing
    void moveFront(){
        if (this.length() > 0){
            cursor = head;
            index = 0;
        }
    }

    //If List is non-empty, places the cursor under the tail element, otherwise does nothing
    void moveBack(){
        if (this.length() > 0){
            cursor = tail;
            index = numItems;
        }
    }

    //move cursor one step toward the front of list if not already there
    void movePrev(){
        if (cursor != null && cursor != head){
            cursor = cursor.prev;
            index--;
        }
        else if (cursor == head){
            index = -1;
            cursor = null;
        }
    }

    //move cursor one step toward the back of the list if not already there
    void moveNext(){
        if (cursor != null && cursor != tail){
            cursor = cursor.next;
            index++;
        }
        else if (cursor == tail){
            index = -1;
            cursor = null;
        }
    }

    //insert new element into this list before the front element
    void prepend(int data){
        Node oldHead = head;
        head = new Node(data);

        if (oldHead != null){
            oldHead.prev = head;
            head.next = oldHead;
        }

        if (numItems == 0) {
            tail = head;
            index++;
        }

        numItems++;
    }

    //inserts new element into the list after the tail.
    void append(int data){
        Node oldTail = tail;
        tail = new Node(data);

        if (oldTail != null){
            oldTail.next = tail;
            tail.prev = oldTail;
        }

        if (numItems == 0){
            head = tail;
            index++;
        }

        numItems++;
    }

    //insert before the cursor element
    void insertBefore(int data){
        if (this.length() > 0 && index >= 0){
            Node N = cursor;
            if (N == head)
                prepend(data);
            else{
                Node P = new Node(data);
                P.next = N;
                P.prev = N.prev;
                N.prev.next = P;
                N.prev = P;
            }
        }
        numItems++;
    }

    //insert after the cursor element
    void insertAfter(int data){
        if (this.length() > 0 && index >= 0){
            Node N = cursor;
	    if (N == tail)
	       append(data);
	    else{
               Node P = new Node(data);
               P.prev = N;
               P.next = N.next;
               N.next.prev = P;
               N.next = P;
	    }
        }
        numItems++;
    }

    //deletes the front element
    void deleteFront(){
        if (this.length() > 0){
            head = head.next;
            head.prev = null;
        }
        numItems--;
    }

    //deletes the back elements
    void deleteBack(){
        if (this.length() > 0){
            tail = tail.prev;
            tail.next = null;
        }
        numItems--;
    }

    //deletes the cursor element, making the cursor undefined
    void delete(){
        Node N = cursor;
        N.next.prev = N.prev;
        N.prev.next = N.next;
        N = null;
        cursor = null;
        numItems--;
    }

    //Returns a String representation of this List
    public String toString(){
        StringBuilder sb = new StringBuilder();
        Node N = head;
        while (N != null){
            sb.append(Integer.toString(N.item)).append("\n");
            N = N.next;
        }
        return new String(sb);
    }

    //Returns a new List representing the same integer sequence, cursor undefined
    List copy(){
        List list = new List();
        Node N = head;
        while(N != null){
            list.append(N.item);
            N = N.next;
        }
        return list;
    }

}
