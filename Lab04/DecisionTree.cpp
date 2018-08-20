#include "DecisionTree.h"

/*Support Function*/
string deleteComma(string input)
{
    for(int i = 0; i < input.size();i++)
    {
        if(input[i] == ',')
        {
            input[i] = ' ';
        }
    }
    return input;
}

bool isNewClass(vector<ChildAttribute> input,string name)
{
    for(int i = 0; i < input.size();i++)
    {
        if(name == input[i].nameChild)
            return false;
    }
    return true;
}

double calEntropy(int numYes, int numNo)
{
    if(numNo == 0 or numYes == 0)
    {
        return 0;
    }
    double result;
    double sum = (double)numNo + numYes;
    result = -(numYes/sum)*log2(numYes/sum) -(numNo/sum)*log2(numNo/sum);
    return result;
}

double calAE(vector<vector<string>>train,AttributeTable input)
{
    double sum;
    double num = train.size();
    for(int i = 0; i < input.table.size();i++)
        sum += ((input.table[i].numYes+input.table[i].numNo)/num)*input.table[i].entropy;
    return sum;
}

/*Main Function*/

bool readFile(vector<vector<string>> &train,string nameFile)
{
    ifstream data(nameFile.c_str());
    if(data.is_open())
    {
        string line;
        string item;
        vector<string> row;
        while(getline(data,line))
        {
            line = deleteComma(line);
            istringstream iss(line);
            while(iss >> item)
                if(item.size())
                    row.push_back(item);
            if(line.size())
            {
                train.push_back(row);
                row.clear();
            }
        }
        data.close();
        return true;
    }
    else return false;
}

vector<string> setOfClassification(vector<vector<string>> train)
{
    vector<string> classification;
    int lastPos = train[0].size() -1;
    string temp = train[1][lastPos];
    classification.push_back(temp);
    for(int i = 1; i < train.size();i++)
        if(temp != train[i][lastPos])
        {
            classification.push_back(train[i][lastPos]);
            return classification;
        }
    return classification;
}

ChildAttribute createChildAttr(vector<vector<string>>trainSet,string nameChild, int column)
{
    int lastPos = trainSet[0].size() -1;
    ChildAttribute temp;
    temp.nameChild = nameChild;
    for(int i = 0; i < trainSet.size();i++)
    {
        if(trainSet[i][column] == nameChild)
        {
            if(trainSet[i][lastPos] == classification[0])
                temp.numYes++;
            else
                temp.numNo++;
        }
    }
    temp.entropy = calEntropy(temp.numYes,temp.numNo);
    return temp;
}

AttributeTable createAttr(vector<vector<string>>trainSet,string nameAttr, int column)
{
    AttributeTable temp;
    temp.nameAttr = nameAttr;
    int lastPos = trainSet[0].size() -1;
    for(int i = 1; i < trainSet.size();i++)
    {
        ChildAttribute check;
        check = createChildAttr(trainSet,trainSet[i][column],column);
        if(isNewClass(temp.table,check.nameChild))
            temp.table.push_back(check);
    }
    temp.ae = calAE(trainSet,temp);
    temp.pos = column;
    return temp;
}

vector<AttributeTable> createAttributeTable(vector<vector<string>> train)
{
    AttributeTable temp;
    vector<AttributeTable> result;
    for(int i = 0; i < train[0].size()-1;i++)
    {
        temp = createAttr(train,train[0][i],i);
        result.push_back(temp);
    }
    return result;
}

AttributeTable getBestAttr(vector<AttributeTable> attribute)
{
    AttributeTable min = attribute[0];
    for(int i = 0; i < attribute.size(); i++)
    {
        if(attribute[i].ae <= min.ae)
        {
            min = attribute[i];
        }
    }
    return min;
}

vector<vector<string>> splitTrainSet(vector<vector<string>> train, string nameValue, int column)
{
    vector<vector<string>> result;
    for(int i = 0; i < train.size();i++)
    {
        vector<string> row;
        if(train[i][column] == nameValue|| i ==0)
            for(int j =0; j < train[i].size();j++)
            {
                if(j != column)
                {
                    row.push_back(train[i][j]);
                }
                else if (i == 0 && j!= column)
                {
                    row.push_back(train[i][j]);
                }
            }                
        if(!row.empty())
            {
                result.push_back(row);
                row.clear();
            }
    }
    return result;
}

int getNumYesNoOfValueInAttribute(AttributeTable attribute,string nameValue,string yn)
{
    for(int i = 0; i < attribute.table.size();i++)
    {
        if(attribute.table[i].nameChild == nameValue && yn == classification[0])
            return attribute.table[i].numYes;
        if(attribute.table[i].nameChild == nameValue && yn == classification[1])
            return attribute.table[i].numNo;
    }
    return -1;
}

Node* ID3Algo(vector<vector<string>> train,vector<AttributeTable> attribute)
{
    Node *root = NULL;
    int lastPos = train[0].size() -1 ;
    AttributeTable attr = createAttr(train,"",lastPos);
    if(attr.table.size() ==1 && attr.table[0].nameChild == classification[0])
    {
        root = new Node;
        root->nameNode = classification[0];
        return root;
    }
    else if(attr.table.size() ==1 && attr.table[0].nameChild == classification[1])
    {
        root = new Node;
        root->nameNode = classification[1];
        return root;
    }
    else if(train[0].size() == 1)
    {
        root = new Node;
        if(getNumYesNoOfValueInAttribute(attr,classification[0],classification[0]) > getNumYesNoOfValueInAttribute(attr,classification[1],classification[1]))
            root->nameNode = classification[0];
        else
            root->nameNode = classification[1];
        return root;
    }
    else
    {
        AttributeTable best = getBestAttr(attribute);
        root = new Node;
        root->nameNode = best.nameAttr;
        for(int i = 0; i< best.table.size();i++)
        {
            Node *childNode = new Node;
            childNode->nameNode = best.table[i].nameChild;
            vector<vector<string>> childTrain = splitTrainSet(train,childNode->nameNode,best.pos);
            vector<AttributeTable> branchAttribute = createAttributeTable(childTrain);
            if(childTrain.empty())
            {
                AttributeTable temp = createAttr(train,"",train.size()-1);
                Node *tempNode = new Node;
                if(getNumYesNoOfValueInAttribute(temp,classification[0],classification[0]) > getNumYesNoOfValueInAttribute(temp,classification[1],classification[1]))
                    tempNode->nameNode = classification[0];
                else
                    tempNode->nameNode = classification[1];
                childNode->child.push_back(tempNode);                    
            }
            else
            {
                Node *tempNode = new Node;
                tempNode = ID3Algo(childTrain,branchAttribute);
                childNode->child.push_back(tempNode);
            }
            root->child.push_back(childNode);
            childTrain.clear();
        }
    }
    return root;
}

Node* doPrediction(Node *root, vector<string> value,int column)
{
    for(int i = 0; i < root->child.size();i++)
    {
        if(root->child[i]->nameNode == value[column])
        {
            return root->child[i];
        }
    }
    return NULL;
}

string Prediction(vector<vector<string>>testSet,Node* root,int row)
{
    for(int i = 0; i < testSet[0].size();i++)
    {
        if(root->nameNode == testSet[0][i])
        {
            Node* temp = doPrediction(root,testSet[row],i);
            if(temp->child.size() == 1)
            {
                if(temp->child[0]->nameNode == classification[0] || temp->child[0]->nameNode == classification[1])
                    return temp->child[0]->nameNode;
                else
                    return Prediction(testSet,temp->child[0],row);
            }
        }
    }
    return "";
}

void deleteTree(Node* root)
{
    if(root == NULL)
        return;
    for (int i = 0; i < root->child.size(); i++) 
    {
		if (root->child[i] != NULL) 
        {
			deleteTree(root->child[i]);
			root->child[i] = NULL;
		}
	}
	delete root;
	root = NULL;
}

void Tree2String(string &result, Node *root,int pos)
{
    if(root->nameNode == classification[0] || root->nameNode == classification[1])
    {
        result.erase(result.size()-1);
        result += " : " ;
        result += root->nameNode;
        result += "\n";
    }
    else
    {
        for(int i = 0; i < pos; i++)
            result += "  ";
        for(int i = 0; i < pos;i++)
            result += "--";
        result += root->nameNode;
        result += "";
        result += "\n";
        pos++;
        for(int i = 0; i < root->child.size();i++)
            Tree2String(result,root->child[i],pos);
    }
}

int main(int argc, char const *argv[])
{
    string nameFile = "train.txt";
    vector<vector<string>> examples;
    if(readFile(examples,nameFile))
    {
        classification = setOfClassification(examples);
        vector<AttributeTable> attribute = createAttributeTable(examples);
        Node *root = ID3Algo(examples,attribute);
        string result;
        Tree2String(result,root,0);
        // cout << "Tree: " << endl;
        // cout << result;
        ofstream writeTree("tree.txt");
        writeTree << result;
        writeTree.close();
        nameFile = "test.txt";
        vector<vector<string>> test;
        if(readFile(test,nameFile))
        {
            ofstream writeTest("Prediction.txt");
            result = "";
            for(int i = 1;i <test.size();i++)
            {
                result += Prediction(test,root,i);
                result += "\n";
            }
            // cout << "Test : " << endl;
            // cout << result;
            writeTest << result;
        }
    }
    return 0;
}
