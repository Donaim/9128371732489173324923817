
#include "pair_relation.h"

const ISetCollection& PairRelation::GetCollection(const KartesianProduct &kp) {
    const ISetCollection* re = ToType<const ISetCollection*>(&kp);
    if(re) 
    {
        if(kp.PairSize.Count() != 2) { throw new SetEx( "Wrong PairSize! Expected=2"); }
        return *re;
    }
    throw new SetEx("Kartesian product is not of ISetCollection!");
}

PairRelation::PairRelation(const KartesianProduct &kProduct, const ISetCollection &scoll)
    : PairRelation(kProduct, *scoll.list[0], *scoll.list[1]) {}

PairRelation::PairRelation(const KartesianProduct &kProduct, const Set &x, const Set &y) : 
    Relation(kProduct), SubSet(kProduct),        
    X(x), Y(y),
    X_FA(ToType<const IForAll*> (&x)), Y_FA(ToType<const IForAll*> (&y)), 
    X_IE(ToType<const IExists*> (&x)), Y_IE(ToType<const IExists*> (&y)) {}

PairRelation::PairRelation(const KartesianProduct &kProduct) : PairRelation(kProduct, GetCollection(kProduct)) {}

bool PairRelation::Defines(const IOrderedSet &o) const { return this->Defines(o.Get(0), o.Get(1)); }


//////////////////////////////////////////////////////////////
// Parts

const Set& PairRelation::Domain() const // dziedzina
{
    if(!Y_IE) { throw new SetEx("Y does not support IExists -> Cannot compute the domain"); }

    TmpPair* pair = new TmpPair{};

    RulePtr rule { [this, pair](const Element &e) 
    {
        pair->x = &e;

        RulePtr rule2 { [this, pair](const Element& e2)
        {
            pair->y = &e2;
            return this->Contains(*pair);
        }};

        return Y_IE->Exists(rule2);
    }};

    return *new RSubSet(X, rule);
}
const Set& PairRelation::Range() const // przeciwdziedzina
{
    if(!X_IE) { throw new SetEx("X does not support IExists -> Cannot compute the codomain"); }
    
    TmpPair* pair = new TmpPair{};

    RulePtr rule { [this, pair](const Element &e) 
    {
        pair->y = &e;

        RulePtr rule2 { [this, pair](const Element& e2)
        {
            pair->x = &e2;
            return this->Contains(*pair);
        }};

        return X_IE->Exists(rule2);
    }};

    return *new RSubSet(Y, rule);
}
const FiniteSet & PairRelation::PairForm() const {
    auto kf = ToType<const FiniteKartesianPSet*>(&Parent);
    if(!kf) { throw new SetEx("Parent KartesianProduct is not finite! Cannot compute PairForm!"); }
    
    return conv<FiniteSet>(kf->Intersect(*this));
}


///////////////////////////////////////////////////////
// Properties

bool PairRelation::IsReflexive() const // zwrotna 
{
    if(!X_FA) { throw new SetEx("X does not support IForAll!"); }
    
    TmpPair* pair = new TmpPair{};

    RulePtr rule {
        [this, pair] (const Element &e) {
            pair->x = &e;
            pair->y = &e;
            return this->Contains(*pair);
        }};

    return X_FA->ForAll(rule);
}
bool PairRelation::IsSymmetric() const // symetryczna
{
    if(!X_FA) { throw new SetEx("X does not support IForAll!"); }
    if(!Y_FA) { throw new SetEx("Y does not support IForAll!"); }
    
    TmpPair* p1 = new TmpPair{};
    TmpPair* p2 = new TmpPair{};

    RulePtr rule {
        [this, p1, p2] (const Element &e) {
            p1->x = &e;
            p2->y = &e;

            RulePtr rule2 {
                [this, p1, p2] (const Element &e2) {
                    p1->y = &e2;
                    p2->x = &e2;

                    if(this->Contains(*p1)) { return this->Contains(*p2); }
                    else { return true; }
            }};

            return Y_FA->ForAll(rule2);
        }};

    return X_FA->ForAll(rule);
}
bool PairRelation::IsTransitive() const // przechodnia
{
    if(!X_FA) { throw new SetEx("X does not support IForAll!"); }
    if(!Y_FA) { throw new SetEx("Y does not support IForAll!"); }
    
    TmpPair* p1 = new TmpPair{}; // x R y
    TmpPair* p2 = new TmpPair{}; // y R z
    TmpPair* p3 = new TmpPair{}; // x R z

    RulePtr ruleX {
        [this, p1, p2, p3] (const Element &ex) {
            p1->x = &ex;
            p3->x = &ex;

            RulePtr ruleY {
                [this, p1, p2, p3] (const Element &ey) {
                    p1->y = &ey;
                    p2->x = &ey;

                    RulePtr ruleY2 {
                        [this, p1, p2, p3] (const Element &ez) {
                            p2->y = &ez;
                            p3->y = &ez;

                            if(this->Contains(*p1) && this->Contains(*p2)) { return this->Contains(*p3); }
                            else { return true; }
                    }};

                    return Y_FA->ForAll(ruleY2);
            }};

            return Y_FA->ForAll(ruleY);
        }};

    return X_FA->ForAll(ruleX);
}
bool PairRelation::IsTotal() const // spojna
{
    if(!X_FA) { throw new SetEx("X does not support IForAll!"); }
    if(!Y_FA) { throw new SetEx("Y does not support IForAll!"); }
    
    TmpPair* p1 = new TmpPair{};
    TmpPair* p2 = new TmpPair{};

    RulePtr rule {
        [this, p1, p2] (const Element &e) {
            p1->x = &e;
            p2->y = &e;

            RulePtr rule2 {
                [this, p1, p2] (const Element &e2) {
                    p1->y = &e2;
                    p2->x = &e2;

                    return this->Contains(*p1) || this->Contains(*p2) || *p1 == *p2;
            }};

            return Y_FA->ForAll(rule2);
        }};

    return X_FA->ForAll(rule);
}
bool PairRelation::IsAsymmetric() const // asymetryczna 
{
    if(!X_FA) { throw new SetEx("X does not support IForAll!"); }
    if(!Y_FA) { throw new SetEx("Y does not support IForAll!"); }
    
    TmpPair* p1 = new TmpPair{};
    TmpPair* p2 = new TmpPair{};

    RulePtr rule {
        [this, p1, p2] (const Element &e) {
            p1->x = &e;
            p2->y = &e;

            RulePtr rule2 {
                [this, p1, p2] (const Element &e2) {
                    p1->y = &e2;
                    p2->x = &e2;

                    if(this->Contains(*p1) && this->Contains(*p2)) { return *p1 == *p2; }
                    else { return true; }
            }};

            return Y_FA->ForAll(rule2);
        }};

    return X_FA->ForAll(rule);
}
bool PairRelation::IsEquivalence() const // relacja rownowaznosci 
{
    return IsReflexive() && IsSymmetric() && IsTransitive();
}
bool PairRelation::IsPartialOrder() const // relacja porzadku
{
    return IsReflexive() && IsAsymmetric() && IsTransitive();
}

//////////////////////////////////////////////////////
//ABSTRAKCJE

const Set & PairRelation::AbstractionClass(const Element & e) const {
    TmpPair* pair = new TmpPair{};
    pair->x = &e;

    RulePtr rule {
        [this, pair] (const Element &y) {
            pair->y = &y;
            return this->Contains(*pair);
        }};

    RSubSet sub = * new RSubSet {Y, rule};

    return Y.Intersect(sub);
}

const FiniteSet & PairRelation::FunctionForm() const {
    auto xf = ToType<const FiniteSet*>(&X);
    if(!xf) { throw new SetEx("X is not FiniteSet ! Cannot compute FunctionForm. "); }

    const int n = X.Size.Count();
    const Element **els = new const Element*[n];

    for(int i = 0, to = n; i < to; i++)
    {
        // cout << "End of " << i << endl ;
        const Element & el = *xf->list[i];
        els[i] = new OrderedPair(el, AbstractionClass(el));
    }

    return *new FiniteSet{els, n};
}
