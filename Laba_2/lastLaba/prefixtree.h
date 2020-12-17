#ifndef PREFIXTREE_H
#define PREFIXTREE_H

#include <QString>
#include <QVector>
#include <map>
#include <QFile>
#include <QDataStream>



using namespace std;
template<class K, class V>
class PrefixTree {
public:
    PrefixTree();
    PrefixTree(PrefixTree &tree);
    ~PrefixTree();

    void delAll();
    bool operator ==(PrefixTree &tree) const;
    bool isKey(const K &key) const;
    V& operator[](const K &key) const;
    QVector<K> getKeys(const K& key) const;


    void add(const K &key,const  V &value);
    void delkey(const K &key);


    bool saveFile(QString &filename) const;
    bool loadFile(QString &filename);

    int getCountNodes() const;
    int getCountKeys() const;

private:

    class Node {
    public:
        Node() {
            parent = nullptr;
            isValue = false;
        }

        ~Node(){
            typename map<K, Node*>::iterator it, end;
            for (auto it =items.begin(); it != items.end(); it++) {
                delete it->second;
            }
        }

        void add(const K key){
            items[key] = new Node;
            items[key]->parent = this;
        }
        V value;
        bool isValue = false;
        Node * parent = nullptr;
        map<K, Node*> items;
    };

    Node *root;
    int countNodes;
    int countKeys;
    int maxLays;
    void addKey(typename PrefixTree<K, V>::Node* root, K* key, const int i, QVector<K>* vect) const;

};





template <class K, class V>
bool PrefixTree <K, V>::isKey(const K &key) const {
    Node *t = root;
    for(int i=0; i< key.size(); i++){
        map<K, Node*> dict = t->items;
        K newkey = {key[i]};
        if(t->items.count(newkey))
            t = dict[newkey];
        else
            return false;
    }
    return t->isValue;

}


template <class K, class V>
PrefixTree <K, V>::PrefixTree() {
    countKeys = countNodes = maxLays = 0;
    root = new Node;
}





template <class K, class V>
PrefixTree<K, V>::~PrefixTree() {
    //Деструктор
    delete root;
}






template <class K, class V>
V& PrefixTree<K, V>::operator[](const K &key) const {
    int i =0;
    Node *t = root;
    for(;i< key.size(); i++) {
        map <K, Node*> dict = t->items;
        K newkey = {key[i]};
        if( t->items.count(newkey))
            t = dict[newkey];
        else
            throw "Key eroor";
    }
    if(t->isValue)
        return  t->value;
    else
        throw "Key eroor";
}








template <class K, class V>
void PrefixTree <K, V>::add(const K &key,const  V &value) {
    Node *node = root;
    int i = 0;
    for(; i < key.size(); i++) {
        K newKey = {key[i]};
        if (node->items.count(newKey) == 0) {
            node->add(newKey);
            countNodes++;
        }
        node = node->items.at(newKey);
    }
    if(node->isValue)
        countKeys--;
    node->value = value;
    node->isValue = true;
    if(maxLays < i)
        maxLays = i;
    countKeys ++;

}


template <class K, class V>
QVector<K> PrefixTree <K, V>::getKeys(const K& key) const {
    QVector<K> vect;
    int i = 0;
    typename PrefixTree<K, V>::Node *t = root;
    K *keyitem = new K;
    for(; i< key.size(); i++) {
        map<K, typename PrefixTree<K, V>::Node*> dict = t->items;
        K newKey = {key[i]};
        if(t->items.count(newKey)){
            t = dict[newKey];
            keyitem->push_back(key[i]);

        }
        else{
            return vect;
        }

    }
    addKey(t,keyitem,i, &vect);
    delete keyitem;
    return vect;

}

template <class K, class V>
void PrefixTree<K, V>::addKey(typename PrefixTree<K, V>::Node* root, K* key, const int i, QVector<K>* vect) const {
    if(root->isValue) {
        vect->push_back(*key);
    }
    typename map<K, typename PrefixTree<K, V>::Node*>::iterator it, end;
    it = root->items.begin();
    end = root->items.end();
    while (it != end) {
        key->push_back((it->first)[0]);
        addKey(it->second, key, i+1, vect);
        // If class K == string use chop(1) else use pop_back();
        key->chop(1);

        it++;
    }
}


template <class K, class V>
void PrefixTree<K, V>::delAll() {
    delete root;
    countKeys = countNodes = maxLays = 0;
    root = new Node;
}


template <class K, class V>
int PrefixTree<K, V>::getCountNodes() const {
    return  countNodes;
}

template <class K, class V>
int PrefixTree<K, V>::getCountKeys() const {
    return  countKeys;
}



template <class K, class V>
PrefixTree <K, V>::PrefixTree(PrefixTree &tree) {
    K emptyCollection;
    QVector<K> vect = tree.getKeys(emptyCollection);
    countKeys = countNodes = maxLays = 0;
    root = new Node;
    int j = 0;

    while (j < vect.size() ) {

        add(vect[j], tree[vect[j]]);
        j++;
    }

}



template<class K, class V>
bool PrefixTree<K, V>::operator ==(PrefixTree &tree) const {
    K emptyCollection;
    QVector<K> vect1 = getKeys(emptyCollection);
    QVector<K> vect2 = tree.getKeys(emptyCollection);
    for(int i=0; i< vect1.size(); i++)
    {
        try {
            if ((*this)[vect1[i]] != tree[vect1[i]])
                return false;
        }
        catch ( out_of_range) {
            return false;
        }
    }

    for(int i=0; i< vect2.size(); i++) {
        try {
            if ((*this)[vect2[i]] != tree[vect2[i]])
                return false;
        }
        catch ( out_of_range) {
            return false;
        }
    }
    return true;
}



template<class K, class V>
void PrefixTree<K, V>::delkey(const K &key) {
    if(isKey(key)) {
        Node *t = root;
        int i = 0;
        for(; i< key.size();i++) {
            map<K, Node*> dict = t->items;
            K newkey = {key[i]};
            t = dict[newkey];
        }
        i--;
        if(t->items.size() != 0 ) {
            t->isValue = false;
            countKeys--;
            return;
        }
        while (t->parent)
            if((t->parent->items.size()== 1) && (t->parent->isValue == 0)) {
                t = t->parent;
                i--;
                countNodes--;
            }
            else
                break;
        if(t->parent){
            K newkey = {key[i]};
            t->parent->items.erase(newkey);
            delete t;
            countNodes--;
        }
        else {
            delete t;
            root = new Node;
        }
        countKeys--;

    }
    else
        throw out_of_range("Key error");
}






template<class K, class V>
bool  PrefixTree <K,V>::saveFile(QString &filename) const {
    if (!filename.endsWith(".lab")) return false;
    QFile file(filename);
    if (file.open(QFile::WriteOnly)) {
        K empty;
        QVector<K> keys = getKeys(empty);
        int i = 0;
        QDataStream out(&file);
        out << QString("DATA");
        out << keys;
        QVector<V> values;
        while (i < keys.size()) {
            values.push_back((*this)[keys[i]]);
            i++;
        }
        out << values;
        file.close();
        return true;
    }
    else
        return false;
}




template<class K, class V>
bool  PrefixTree <K,V>::loadFile(QString &filename) {
    if (!filename.endsWith(".lab")) return false;
    QFile file(filename);
    if (file.open(QFile::ReadOnly)) {
        QDataStream in(&file);
        QString pass;
        in >> pass;
        if (pass != "DATA") {
            file.close();
            return false;
        }
        delAll();
        QVector<K> keys;
        in >> keys;
        QVector<V> values;
        in >> values;

        for(int i = 0; i<keys.size(); i++)
            add(keys[i],values[i]);
        file.close();
        return true;
    }
    else
        return false;
}


#endif // PREFIXTREE_H
