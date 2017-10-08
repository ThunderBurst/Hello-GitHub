AVLTree Delete( AVLTree T, ElementType X )
{
	AVLTree temp;
	
    if ( !T ) { 
		//并没有找到
		return NULL;
    } 
 
    else if ( X < T->Data ) {
		//要删除的节点在左子树里面
        T->Left = Delete( T->Left, X);
       
        if ( GetHeight(T->Left)-GetHeight(T->Right) == -2 )
			//左子树的删除导致了不平衡
            if ( GetHeight(T->Right->Left)>GetHeight(T->Right->Right) ) 
				//需要向右提起保持平衡，如果右儿子的左子树较高，即A==L B==L-1，对应case3
				T = DoubleRightLeftRotation(T);      
            else 
				//对应case1，case2
                T = SingleRightRotation(T); 
    } 
     
    else if ( X > T->Data ) {
		//要删除的节点在右子树里面
        T->Right = Delete( T->Right, X );

        if ( GetHeight(T->Left)-GetHeight(T->Right) == 2 )
			//右子树的删除导致了不平衡
            if ( GetHeight(T->Left->Right)>GetHeight(T->Left->Right) ) 
				//需要向左提起保持平衡，操作和上面是对称的
                T = DoubleLeftRightRotation(T);     
            else 
                T = SingleLeftRotation(T); 
    } 
	else if (T->Left&&T->Right){
		//双子节点删除问题，转化为单子节点或无子节点删除问题
		temp = FindMin(T->Right);
		T->Data = temp->Data;
		T->Right = Delete(T->Right,T->Data);
	}
	else{
		//单子或无子删除
		temp = T;
		if (!T->Left)
			T = T->Right;
		else if (!T->Right)
			T = T->Left;
		free(temp);
	}
	if (T){
		//更新高度
		//如果删除的是叶节点，那么T==NULL，需要检测一次
		T->Height = Max( GetHeight(T->Left), GetHeight(T->Right) ) + 1;
	}
     
    return T;
}