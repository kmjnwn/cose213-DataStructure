//
// Implementation
//
template <typename E>					// constructor
  AVLTree<E>::AVLTree() : ST() { }

template <typename E>					// node height utility
  int AVLTree<E>::height(const TPos& v) const
  {
    return (v.isExternal() ? 0 : (*v).height());
  }

template <typename E>					// set height utility
  void AVLTree<E>::setHeight(TPos v) { 
    int hl = height(v.left());
    int hr = height(v.right());
    (*v).setHeight(1 + std::max(hl, hr));			// max of left & right
  }

template <typename E>					// is v balanced?
  bool AVLTree<E>::isBalanced(const TPos& v) const {	
    int bal = height(v.left()) - height(v.right());
    return ((-1 <= bal) && (bal <= 1));
  }

template <typename E>					// get tallest grandchild
  typename AVLTree<E>::TPos AVLTree<E>::tallGrandchild(const TPos& z) const {
    TPos zl = z.left();
    TPos zr = z.right();
    if (height(zl) >= height(zr))			// left child taller
      if (height(zl.left()) >= height(zl.right()))
        return zl.left();
      else
        return zl.right();
    else 						// right child taller
      if (height(zr.right()) >= height(zr.left()))
        return zr.right();
      else
        return zr.left();
  }


//
// ToDo
//

template <typename E>					// remove key k entry
  void AVLTree<E>::erase(const K& k) {
    
    // ToDo
    TPos v = ST::finder(k, ST::root()); // find in base tree
    if (Iterator(v) == ST::end()){ // not found?
      throw ("Erase of nonexistent");
    }
    TPos w = ST::eraser(v); // remove it
    rebalance(w);
  }

template <typename E>					// insert (k,x)
  typename AVLTree<E>::Iterator AVLTree<E>::insert(const K& k, const V& x) {
    
    // ToDo
    TPos v = ST::inserter(k, x); // insert in base tree
    setHeight(v); // compute its height
    rebalance(v); // rebalance if needed
    return Iterator(v);
  }
  
template <typename E>					// rebalancing utility
  void AVLTree<E>::rebalance(const TPos& v) {
    
    // ToDo
    TPos z = v;
    while (!(z == ST::root())) { // rebalance up to root
      z = z.parent();
      setHeight(z); // compute new height
      if (!isBalanced(z)) { // restructuring needed
        TPos x = tallGrandchild(z);
        z = restructure(x); // trinode restructure
        setHeight(z.left()); // update heights
        setHeight(z.right());
        setHeight(z);
      }
    }
  }

template <typename E>				// Binary Search Tree Rotation
  typename AVLTree<E>::TPos AVLTree<E>::restructure(const TPos& v) {

	// ToDo
  int vv = (*v).key(), vp = (*v.parent()).key(), vgp = (*v.parent().parent()).key();

  TPos a, b, c, t0, t1, t2, t3;

  if( vgp < vv ){
    if(vv > vp){ //  RR
      c = v; b = v.parent(); a = v.parent().parent();
      t0 = a.left(); t1 = b.left(); t2 = c.left(); t3 = c.right();
    }
    else{ // RL
      c = v.parent(); b = v; a = v.parent().parent();
      t0 = a.left(); t1 = b.left(); t2 = b.right(); t3 = c.right();
    }
    a.v->right = t1.v;
    t1.v->par = a.v;
    c.v->left = t2.v;
    t2.v->par = c.v;
    if (v.v->par->par->par->right == a.v) v.v->par->par->par->right = b.v;
    else v.v->par->par->par->left = b.v;
  }
  else{
    if(vv > vp){ // LR
      c = v.parent().parent(); b = v; a = v.parent();
      t0 = a.left(); t1 = b.left(); t2 = b.right(); t3 = c.right();
    }
    else{ // LL
      a = v; b = v.parent(); c = v.parent().parent();
      t0 = a.left(); t1 = a.right(); t2 = b.right(); t3 = c.right();
    }
    c.v->left = t2.v;
    t2.v->par = c.v;
    a.v->right = t1.v;
    t1.v->par = a.v;
    if (v.v->par->par->par->right == c.v) v.v->par->par->par->right = b.v;
    else v.v->par->par->par->left = b.v;
  }

  b.v->par = v.v->par->par->par;
  
  b.v->left = a.v;
  b.v->right = c.v;
  a.v->par = b.v;
  c.v->par = b.v;

  return b;
  }
