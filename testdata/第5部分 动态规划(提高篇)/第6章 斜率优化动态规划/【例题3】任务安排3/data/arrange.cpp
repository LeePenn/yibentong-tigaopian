#include<iostream>
#include<stdio.h>
#include<math.h>
#include<map>

using namespace std ;

struct SBTree {
	__int64 x, y ;
	SBTree *pL, *pR, *pB, *pF ;
	int size ;
private :
	static int getSize(SBTree* node) {
		return node != NULL ? node->size : 0 ;
	}	
	void update() {
		size = getSize(pL) + getSize(pR) + 1 ;
	}
	SBTree* leftRorate() {
		SBTree* _pR = pR ;
		pR = pR->pL, _pR->pL = this ;
		update(); _pR->update() ;
		return _pR ;
	}
	SBTree* rightRorate() {
		SBTree* _pL = pL ;
		pL = pL->pR, _pL->pR = this ;
		update(); _pL->update() ;
		return _pL ;
	}
	SBTree* maintain(int type = 3) {
		SBTree* root ;
			   if (type&1 && pR != NULL && 
			getSize(pL) < max(getSize(pR->pL), getSize(pR->pR))) {
			if (getSize(pL) < getSize(pR->pL))
				pR = pR->rightRorate() ;
			root = leftRorate() ;
		} else if (type&2 && pL != NULL &&
			getSize(pR) < max(getSize(pL->pL), getSize(pL->pR))) {
			if (getSize(pR) < getSize(pL->pR)) 
				pL = pL->leftRorate() ;
			root = rightRorate() ;
		} else return this ;
		if (root->pL != NULL)
			root->pL = root->pL->maintain(2) ;
		if (root->pR != NULL)
			root->pR = root->pR->maintain(1) ;
		return root->maintain() ;
	}
public :
	SBTree(__int64 _x = 0, __int64 _y = 0) {
		x = _x ; y = _y ;
		pL = pR = pB = pF = NULL ;
		size = 1 ;
	}
	
	void* operator new (size_t size) ;
	bool operator < (SBTree* that) {
		return this->x < that->x ||
			this->x == that->x && this->y < that->y ;
	}
	bool operator == (SBTree* that) {
		return this->x == that->x && this->y == that->y ;
	}
	
	static double getAngle(SBTree* r, SBTree* l) {
		if (l == NULL) return  1e100 ;
		if (r == NULL) return -1e100 ;
		if (fabs(double(l->y - r->y)) <= 1e-8) 
			return 1e100 ;
		return double(l->x - r->x) / (l->y - r->y) ;
	}
	
	SBTree* add(SBTree* node) {
		//if (this == NULL)
		//	printf("ERROR in add\n") ;
		//printf("add this=%d\n", this) ;
		if (*node == this)
			return this ;
		if (*node < this) { 
			if (pL != NULL) {
				pL = pL->add(node) ;
			} else {
				pL = node ;
				node->pB = pB ;
				if (pB != NULL) 
					pB->pF = node ;
				node->pF = this ;
				this->pB = node ;
			}
		} else {
			if (pR != NULL) {
				pR = pR->add(node) ;
			} else {
				pR = node ;
				node->pF = pF ;
				if (pF != NULL)
					pF->pB = node ;
				node->pB = this ;
				this->pF = node ;
			}
		}
		return size++, maintain() ;
	}
	
	SBTree* getOptNode(__int64 angle) {
		//if (this == NULL)
		//	printf("ERROR in getOptNode\n") ;
		if (angle < getAngle(pB, this))
			return pL->getOptNode(angle) ;
		if (angle > getAngle(this, pF))
			return pR->getOptNode(angle) ;
		return this ;
	}
	
	SBTree* getMaxNode() {
		//if (this == NULL)
		//	printf("ERROR in deleteMaxNode\n") ;
		return (pR == NULL) ? this : pR->getMaxNode() ;
	}
			
	SBTree* deleteNode(SBTree* node, bool chainAble = true) {
		//if (this == NULL) 
		//	printf("ERROR in deleteNode node=%d\n", node) ;
		if (*node == this) {
			if (chainAble) {
				if (pB != NULL) pB->pF = pF ;
				if (pF != NULL) pF->pB = pB ;
			}
			if (pL == NULL) return pR ;
			if (pR == NULL) return pL ;
			SBTree* maxNode = node->pL->getMaxNode() ;
			pL = pL->deleteNode(maxNode, false) ;
			maxNode->pL = pL ;
			maxNode->pR = pR ;
			maxNode->update() ;
			return maxNode->maintain() ;
		}
		if (*node < this) pL = pL->deleteNode(node, chainAble) ;
				else	  pR = pR->deleteNode(node, chainAble) ;
		return size--, maintain() ;
	}
	
	void debug() {
		if (pL != NULL) pL->debug() ;
		printf("this=%8d pL=%8d pR=%8d pB=%8d pF=%8d\n",
			this, pL, pR, pB, pF) ;/*
		printf("x=%d y=%d back=%.4lf front=%.4lf\n",
			x, y, pB ? getAngle(pB, this) : -1.0, 
				pF ? getAngle(this, pF) : -1.0
		) ;*/
		if (pR != NULL) pR->debug() ;
	}
	
} ;

struct MemoryPond {
private :
	static const int SIZE = 5000000 ;
	int memory[SIZE] ; 
	void* top ;
public :
	MemoryPond() {
		top = (void*) &memory[0] ;
	}
	void* getMemory(size_t size) {
		top = (void*) ((int) top + size) ;
		return (void*) ((int) top - size) ;
	}
} ;

MemoryPond pond ;

void* SBTree::operator new (size_t size) {
	return pond.getMemory(size) ;
}

const int MaxN = 1001000 ;
int N, S ;
__int64 t[MaxN], c[MaxN], st[MaxN], sc[MaxN], f[MaxN] ;

__int64 solve2() {
	SBTree* root = new SBTree(0, 0) ;
	for (int i = N ; i >= 1 ; i--) {
		SBTree* node = root->getOptNode(sc[i]) ;
		f[i] = node->x + (st[i] - node->y + S) * sc[i] ;
		//printf("f[%d]=%I64d\n", i, f[i]) ;
		node = new SBTree(f[i], st[i]) ;
		root = root->add(node) ;
		//root->debug() ; printf("\n") ;		
		//printf("new node = %d\n", node) ; 
		while (node->pB != NULL &&
			SBTree::getAngle(node->pB->pB, node->pB) >
			SBTree::getAngle(node->pB, node)) 
				root = root->deleteNode(node->pB) ;
		while (node->pF != NULL &&
			SBTree::getAngle(node->pF->pF, node->pF) <
			SBTree::getAngle(node->pF, node)) {
				//root->debug() ; printf("\n") ;
				//printf("deleteNode : %d\n", node->pF) ;
				root = root->deleteNode(node->pF) ;
				//root->debug() ; printf("\n") ;
			}
		if (SBTree::getAngle(node->pB, node) >
			SBTree::getAngle(node, node->pF)) {
				//root->debug() ; printf("\n") ;
				//printf("deleteNode : %d\n", node->pB) ;				 
				root = root->deleteNode(node->pB) ;
				//root->debug() ; printf("\n") ;
			}

		//root->debug() ; printf("\n") ;
	}
	return f[1] ;
}

int que[MaxN] ;

double getAngle(int r, int l) {
	if (st[l] - st[r] <= 1e-6)
		return 1e100 ;
	return double(f[l] - f[r]) / (st[l] - st[r]) ;
}

__int64 solve1() { 
	int top = 1, target = 1 ;
	que[top] = N + 1 ;
	for (int i = N ; i >= 1 ; i--) {
		while (target < top && getAngle(que[target], que[target+1]) 
			<= sc[i]) target++ ;
		/*
		printf("top=%d target=%d\n",
			top, target) ;
		for (int j = 1 ; j <= top ; j++) {
			if (j != 1) printf("%.4lf ", 
				getAngle(que[j-1], que[j])) ;
			printf("%d ", que[j]) ;
		}
		printf("\n") ;
		*/
		f[i] = f[que[target]] + (st[i] - st[que[target]] + S) * sc[i] ;
		while (top > 1 && getAngle(que[top-1], que[top]) > 
			getAngle(que[top], i)) top-- ;
		que[++top] = i ;
		target = min(target, top) ;
		//printf("f[%d]=%d\n", i, f[i]) ;
	}
	return f[1] ;
}

__int64 solve3() {
	for (int i = N ; i >= 1 ; i--) {
		f[i] = (__int64)0x3f3f3f3f * 0x3f3f3f3f ;
		for (int j = i + 1 ; j <= N + 1 ; j++)
			f[i] = min(f[i], f[j] + (st[i] - st[j] + S) * sc[i]) ;
		//printf("f[%d]=%I64d\n", i, f[i]) ;
	}
	return f[1] ;
}

int main() {
	freopen("arrange.in", "r", stdin) ;
	freopen("arrange.out", "w", stdout) ;
	scanf("%d%d", &N, &S) ;
	bool hasNagi = false ;
	for (int i = 1 ; i <= N ; i++) {
		scanf("%I64d%I64d", &t[i], &c[i]) ;
		if (t[i] < 0) hasNagi = true ;
	}
	for (int i = N ; i >= 1 ; i--) {
		st[i] = st[i+1] + t[i] ;
		sc[i] = sc[i+1] + c[i] ;
		//printf("i=%d st=%d sc=%d\n",
		//	i, st[i], sc[i]) ;
	}
	if (!hasNagi) printf("%I64d\n", solve1()) ;
       else       printf("%I64d\n", solve2()) ;
	//printf("%I64d\n", solve3()) ;
	return 0 ;
}

