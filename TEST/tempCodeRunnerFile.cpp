    cpw[i].push_back(C);
        cpw[i].push_back(P);
        cpw[i].push_back(W);
    }
    int tmp;
    for(int i=0;i<N;i++){
        cin >> tmp;
        product.push_back(tmp);
    }
    
    list <int> max = product;
    max.sort();
    for(int i=0;i<K;i++){
        int count = 0;
        int tmpto = 0;
        int x = 0;
        if(cpw[i][2] >= max.back());
        for(auto j=product.begin();j!=product.end();j++){
            if(tmpto+*j > cpw[i].back()){
                count += 1;
                tmpto = 0;