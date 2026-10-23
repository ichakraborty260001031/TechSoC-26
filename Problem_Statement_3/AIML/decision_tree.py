import numpy as np

class Node:
    def __init__(self,threshold=None,feature=None,category=None,prediction=None):
        self.left=None
        self.right=None
        self.feature=feature
        self.threshold=threshold
        self.prediction=prediction
        self.category=category
        

class Tree:
    def __init__(self,inp,tar,feature_types):
        self.root=None
        self.inputs=inp
        self.targets=tar
        self.feature_types=feature_types

    def build_tree(self):
        self.root=self.build_subtree(self.inputs,self.targets)

    def build_subtree(self,inp,tar):
        if entropy(tar)==0:
            return Node(None,None,None,tar[0])

        feature,response,gain,f_type=best_split(inp,tar,self.feature_types) #response could be string or num

        if gain<=0:
            cnts=np.unique_counts(tar)
            max_i=0
            max_c=0
            for i in range(len(cnts.values)):
                if cnts.counts[i]>max_c:
                    max_c=cnts.counts[i]
                    max_i=i

            return Node(None,None,None,cnts.values[max_i])
        
        if(f_type=="Numerical"):
            dummy_root=Node(response,feature,None)
            left_mask=inp[:,feature]<response
            right_mask=inp[:,feature]>=response
        else:
            dummy_root=Node(None,feature,response)
            left_mask=inp[:,feature]==response
            right_mask=inp[:,feature]!=response
        

        left_inp=inp[left_mask]
        left_tar=tar[left_mask]
        right_inp=inp[right_mask]
        right_tar=tar[right_mask]


        dummy_root.left=self.build_subtree(left_inp,left_tar)
        dummy_root.right=self.build_subtree(right_inp,right_tar)

        return dummy_root

    def predict(self,val):
        n=self.root
        while(n.feature!=None):
            if n.threshold!=None:
                if val[n.feature]<n.threshold:
                    n=n.left
                else:
                    n=n.right
            elif n.category!=None:
                if val[n.feature]==n.category:
                    n=n.left
                else:
                    n=n.right

        return n.prediction




def entropy(arr):
    uniques=np.unique_counts(arr)
    epy=0
    for i in range(len(uniques.values)):
        pi=uniques.counts[i]/np.sum(uniques.counts)
        epy+=-pi*np.log2(pi)

    return epy

def best_split(x,y,feature_types):
    
    par_epy = entropy(y)
    #generate all thresholds
    possibitites=[]

    for i in range(len(x[0])):
        if feature_types[i]=="Numerical":
            values=np.sort(x[:,i])
            temp=[]
            for j in range(len(values)-1):
                threshold=(values[j]+values[j+1])/2
                temp.append(threshold)
            possibitites.append(temp)
        else:
            temp=[]
            for j in range(len(x[:,i])):
                temp.append(x[j,i])
            temp=np.unique(temp)
            possibitites.append(temp)

    p_bility=possibitites
    best_gain=-1
    best_stuff=-1
    best_feature=-1
    best_type="Numerical"
    for i in range(len(p_bility)):
        for j in range(len(p_bility[i])):
            if(feature_types[i]=="Numerical"):
                left=x[:,i]<p_bility[i][j]
                right=x[:,i]>=p_bility[i][j]
            else:
                left=x[:,i]==p_bility[i][j]
                right=x[:,i]!=p_bility[i][j]

            if not np.any(left) or not np.any(right):
                continue
            lval,lcnt=np.unique(y[left],return_counts=True)
            rval,rcnt=np.unique(y[right],return_counts=True)

            #information gain
            residue=0
            residue+=np.sum(left)*entropy(y[left])+np.sum(right)*entropy(y[right])
            residue=residue/len(y)
            if par_epy-residue>best_gain:
                best_gain=par_epy-residue
                best_feature=i
                best_stuff=p_bility[i][j]

    if best_feature == -1:
        return -1, None, 0, None

    if(feature_types[best_feature]=="Categorical"):
        best_type="Categorical"
    return best_feature,best_stuff,best_gain,best_type

# Features: [study_hours, sleep_hours, IQ]



