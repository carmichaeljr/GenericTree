template <typename T>
Tree<T>::iterator::iterator(void){
	this->prevAction=Tree<T>::mvDown;
	this->revisit=false;
	this->node=nullptr;
}

template <typename T>
Tree<T>::iterator::iterator(typename Tree<T>::Node *headNode, bool revisit){
	this->prevAction=Tree<T>::mvDown;
	this->revisit=revisit;
	this->node=headNode;
}

template <typename T>
typename Tree<T>::iterator& Tree<T>::iterator::operator++(const int num){
	if (this->node==nullptr){
		this->prevAction=-1;
	} else if (this->hasChildren(this->node)){
		if (this->prevAction==Tree<T>::mvDown || this->prevAction==Tree<T>::mvNext){
			this->move(Tree<T>::mvDown);
		} else if (this->hasNext(this->node)){	//prevAction was up
			this->move(Tree<T>::mvNext);
		} else if (!this->hasNext(this->node)){	//prevAction was up
			this->move(Tree<T>::mvUp);
		}
	} else {	//!this->hasChildren(this->node);
		if (this->hasNext(this->node)){
			this->move(Tree<T>::mvNext);
		} else {	//!this->hasNext(this->node)
			this->move(Tree<T>::mvUp);
		}
	}
	return *this;
}

template <typename T>
constexpr bool Tree<T>::iterator::hasChildren(typename Tree<T>::Node *node) const {
	return (node->child!=nullptr);
}

template <typename T>
constexpr bool Tree<T>::iterator::hasNext(typename Tree<T>::Node *node) const {
	return (node->next!=nullptr);
}

template <typename T>
constexpr bool Tree<T>::iterator::hasParent(typename Tree<T>::Node *node) const {
	return (node->parent!=nullptr);
}

template <typename T>
void Tree<T>::iterator::move(const int dir){
	switch(dir){
		case (Tree<T>::mvNext): this->node=this->node->next; 
					this->prevAction=Tree<T>::mvNext; break;
		case (Tree<T>::mvDown): this->node=this->node->child; 
					this->prevAction=Tree<T>::mvDown; break;
		case (Tree<T>::mvUp): this->node=this->node->parent; 
					this->prevAction=Tree<T>::mvUp; break;
		default: break;
	}
	if (!this->revisit && this->prevAction==Tree<T>::mvUp){
		this->operator++(1);
	}
}

//Do not attempt to access when iterator==end(), undefined behavior, similar to std::vector
template <typename T>
T& Tree<T>::iterator::operator*(void){
	return this->node->data;
}
template <typename T>
T& Tree<T>::iterator::operator*(void) const {
	return this->node->data;
}

template <typename T>
T* Tree<T>::iterator::operator->(void){
	return (&this->node->data);
}
template <typename T>
T* Tree<T>::iterator::operator->(void) const {
	return (&this->node->data);
}
