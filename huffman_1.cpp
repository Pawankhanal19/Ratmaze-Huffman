// C++ program for Huffman Coding with Decoding implementation   
#include <iostream> 
#include <cstdlib>  
using namespace std;

// This constant can be avoided by explicitly   
// calculating height of Huffman Tree   
#define MAX_TREE_HT 100   

// A Huffman tree node 
struct MinHeapNode {
    // One of the input characters     
    char data;   
    // Frequency of the character     
    unsigned freq;

    // Left and right child of this node       
    struct MinHeapNode *left, *right;   
};

// A Min Heap: Collection of 
// minheap (or Huffman tree) nodes 
struct MinHeap {
    // Current size of min heap     
    unsigned size;   
    // capacity of min heap       
    unsigned capacity;
    // Array of minheap node pointers       
    struct MinHeapNode** array;   
};

// A utility function allocate a new
// min heap node with given character
// and frequency of the character   
struct MinHeapNode* newNode(char data, unsigned freq)   
{
    struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;     
    temp->data = data;       
    temp->freq = freq;

    return temp;
}

// A utility function to create   
// a min heap of given capacity   
struct MinHeap* createMinHeap(unsigned capacity)
{
    struct MinHeap* minHeap
        = (struct MinHeap*)malloc(sizeof(struct MinHeap));

    // current size is 0       
    minHeap->size = 0;   
    minHeap->capacity = capacity;
    minHeap->array
        = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));     
    
    return minHeap;
}

// A utility function to   
// swap two min heap nodes  
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// The standard minHeapify function.   
void minHeapify(struct MinHeap* minHeap, int idx)
{
    int smallest = idx;     
    int left = 2 * idx + 1;       
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)         
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)         
        smallest = right;           
    
    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);           
        minHeapify(minHeap, smallest);
    }
}

// A utility function to check   
// if size of heap is 1 or not 
int isSizeOne(struct MinHeap* minHeap)   
{
    return (minHeap->size == 1);
}

// A standard function to extract 
// minimum value node from heap   
struct MinHeapNode* extractMin(struct MinHeap* minHeap)   
{
    struct MinHeapNode* temp = minHeap->array[0];     
    minHeap->array[0] = minHeap->array[minHeap->size - 1];

    --minHeap->size;       
    minHeapify(minHeap, 0);

    return temp;
}

// A utility function to insert 
// a new node to Min Heap 
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) {
    ++minHeap->size;      
    int i = minHeap->size - 1;      
    
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];         
        i = (i - 1) / 2;
    }

    minHeap->array[i] = minHeapNode;
}

// A standard function to build min heap   
void buildMinHeap(struct MinHeap* minHeap)   
{
    int n = minHeap->size - 1;     
    int i;
    
    for (i = (n - 1) / 2; i >= 0; --i)           
        minHeapify(minHeap, i);
}

// A utility function to print an array of size n 
void printArr(int arr[], int n)   
{
    int i;       
    for (i = 0; i < n; ++i)           
        cout << arr[i];
    
    cout << "\n";
}

// Utility function to check if this node is leaf   
int isLeaf(struct MinHeapNode* root)   
{
    return !(root->left) && !(root->right);
}

// Creates a min heap of capacity   
// equal to size and inserts all character of   
// data[] in min heap. Initially size of  
// min heap is equal to capacity   
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size)
{
    struct MinHeap* minHeap = createMinHeap(size);
    
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);

    minHeap->size = size;       
    buildMinHeap(minHeap);

    return minHeap;
}

// The main function that builds Huffman tree  
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size)   
{
    struct MinHeapNode *left, *right, *top;

    // Step 1: Create a min heap of capacity
    // equal to size. Initially, there are
    // modes equal to size.   
    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    // Iterate while size of heap doesn't become 1     
    while (!isSizeOne(minHeap)) {
        // Step 2: Extract the two minimum
        // freq items from min heap         
        left = extractMin(minHeap);   
        right = extractMin(minHeap);
        
        // Step 3: Create a new internal
        // node with frequency equal to the
        // sum of the two nodes frequencies.
        // Make the two extracted node as
        // left and right children of this new node.   
        // Add this node to the min heap   
        // '$' is a special value for internal nodes, not used         
        top = newNode('$', left->freq + right->freq);              
        top->left = left;           
        top->right = right;   

        insertMinHeap(minHeap, top);
    }

    // Step 4: The remaining node is the
    // root node and the tree is complete.      
    return extractMin(minHeap);
}

// Prints huffman codes from the root of Huffman Tree.   
// It uses arr[] to store codes  
void printCodes(struct MinHeapNode* root, int arr[], int top)
{
    // Assign 0 to left edge and recur     
    if (root->left) {
        arr[top] = 0;          
        printCodes(root->left, arr, top + 1);
    }

    // Assign 1 to right edge and recur     
    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    // If this is a leaf node, then   
    // it contains one of the input   
    // characters, print the character
    // and its code from arr[]      
    if (isLeaf(root)) {
        cout << root->data << ": ";          
        printArr(arr, top);
    } 
}

// Store Huffman codes in a string array
void storeCodes(struct MinHeapNode* root, int arr[], int top, char* huffCodes[], char data[], int size)
{
    // Assign 0 to left edge and recur     
    if (root->left) {
        arr[top] = 0;          
        storeCodes(root->left, arr, top + 1, huffCodes, data, size);
    }

    // Assign 1 to right edge and recur     
    if (root->right) {
        arr[top] = 1;
        storeCodes(root->right, arr, top + 1, huffCodes, data, size);
    }

    // If this is a leaf node, then store the code
    if (isLeaf(root)) {
        // Find the index of this character in the data array
        int idx = -1;
        for (int i = 0; i < size; i++) {
            if (data[i] == root->data) {
                idx = i;
                break;
            }
        }
        
        if (idx != -1) {
            // Allocate memory for the code string
            huffCodes[idx] = (char*)malloc((top + 1) * sizeof(char));
            
            // Convert int array to char array (0 and 1 as characters)
            for (int i = 0; i < top; i++) {
                huffCodes[idx][i] = arr[i] + '0';
            }
            huffCodes[idx][top] = '\0'; // Null-terminate the string
        }
    } 
}

// Function to encode input text using Huffman codes
char* encode(char* text, char* huffCodes[], char data[], int size)
{
    // Count the total length needed for the encoded string
    int len = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        // Find the corresponding code for this character
        for (int j = 0; j < size; j++) {
            if (data[j] == text[i]) {
                // Add the length of this code
                int codeLen = 0;
                while (huffCodes[j][codeLen] != '\0') {
                    codeLen++;
                }
                len += codeLen;
                break;
            }
        }
    }
    
    // Allocate memory for encoded string
    char* encodedText = (char*)malloc((len + 1) * sizeof(char));
    encodedText[0] = '\0'; // Initialize as empty string
    
    // Encode the text
    for (int i = 0; text[i] != '\0'; i++) {
        // Find the corresponding code for this character
        for (int j = 0; j < size; j++) {
            if (data[j] == text[i]) {
                // Concatenate this code to the encoded string
                strcat(encodedText, huffCodes[j]);
                break;
            }
        }
    }
    
    return encodedText;
}

// Function to recursively decode the encoded text
// This implements the Huffman decoding algorithm as described in the assignment
void decodeHelper(struct MinHeapNode* root, struct MinHeapNode* curr, char* encodedText, int* index, char* decodedText, int* decodedIndex)
{
    // If we've reached a leaf node, we found a character
    if (isLeaf(curr)) {
        decodedText[*decodedIndex] = curr->data;
        (*decodedIndex)++;
        
        // If we've processed all bits, return
        if (encodedText[*index] == '\0')
            return;
        
        // Start again from the root for the next character
        decodeHelper(root, root, encodedText, index, decodedText, decodedIndex);
        return;
    }
    
    // If encoded text has ended but we haven't reached a leaf, something is wrong
    if (encodedText[*index] == '\0')
        return;
    
    // Move left if current bit is '0', otherwise move right
    if (encodedText[*index] == '0') {
        (*index)++;
        decodeHelper(root, curr->left, encodedText, index, decodedText, decodedIndex);
    } else {
        (*index)++;
        decodeHelper(root, curr->right, encodedText, index, decodedText, decodedIndex);
    }
}

// Function to decode the Huffman encoded text
char* decode(struct MinHeapNode* root, char* encodedText)
{
    // Calculate the maximum possible length of the decoded text
    // (very rough estimate - in worst case, each bit represents one character)
    int maxLen = 0;
    while (encodedText[maxLen] != '\0')
        maxLen++;
    
    // Allocate memory for decoded text (add 1 for null terminator)
    char* decodedText = (char*)malloc((maxLen + 1) * sizeof(char));
    
    // Initialize index variables
    int index = 0;       // Index for encoded text
    int decodedIndex = 0;  // Index for decoded text
    
    // Use recursive function to decode
    decodeHelper(root, root, encodedText, &index, decodedText, &decodedIndex);
    
    // Add null terminator
    decodedText[decodedIndex] = '\0';
    
    return decodedText;
}

// The main function that builds a Huffman Tree and
// print codes by traversing the built Huffman Tree
void HuffmanCodes(char data[], int freq[], int size)
{
    // Construct Huffman Tree
    struct MinHeapNode* root = buildHuffmanTree(data, freq, size);

    // Print Huffman codes using
    // the Huffman tree built above
    int arr[MAX_TREE_HT], top = 0;
    
    cout << "Huffman Codes:" << endl;
    printCodes(root, arr, top);
}

// Driver code 
int main()
{
    char arr[] = {'A', 'B', 'C', 'D', 'E'};
    int freq[] = {5, 1, 6, 3, 2};

    int size = sizeof(arr) / sizeof(arr[0]);

    // Print Huffman codes
    cout << "Original character set and frequencies:" << endl;
    for (int i = 0; i < size; i++) {
        cout << arr[i] << ": " << freq[i] << endl;
    }
    cout << endl;

    // Construct Huffman Tree
    struct MinHeapNode* root = buildHuffmanTree(arr, freq, size);

    // Print Huffman codes
    int codeArr[MAX_TREE_HT], top = 0;
    cout << "Huffman Codes:" << endl;
    printCodes(root, codeArr, top);
    
    // Store Huffman codes in an array for encoding
    char* huffCodes[size];
    storeCodes(root, codeArr, top, huffCodes, arr, size);
    
    // Original text to encode
    char text[] = "AABCADE";
    cout << "\nOriginal text: " << text << endl;
    
    // Encode the text
    char* encodedText = encode(text, huffCodes, arr, size);
    cout << "Encoded text: " << encodedText << endl;
    
    // Decode the text using recursive function
    char* decodedText = decode(root, encodedText);
    cout << "Decoded text: " << decodedText << endl;
    
    // Free allocated memory
    free(encodedText);
    free(decodedText);
    for (int i = 0; i < size; i++) {
        free(huffCodes[i]);
    }
    
    return 0;
}