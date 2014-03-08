#pragma once

BEGIN_NAMESPACE(epi_18)
void SolveReaderWriterProblem() {
    vector<int> shared_mem = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    mutex lock;
    int stop_writer = false;

    thread writer([&] {
        default_random_engine e((random_device())());
        uniform_int_distribution<> d(0, 9);
        while (!stop_writer) {
            {
                lock_guard<mutex> guard(lock);
                shared_mem[d(e)] = d(e);
            }
            std::chrono::milliseconds dura(50);
            std::this_thread::sleep_for(dura);
        }
    });

    vector<thread> readers;
    for (int i = 0; i < 5; ++i) {
        readers.push_back(thread([&](){
                lock_guard<mutex> guard(lock);
                copy(begin(shared_mem), end(shared_mem), ostream_iterator<int>(cout, " "));
                cout << endl;
            } ));
    }
    
    stop_writer = true;
    for (auto& t : readers)
        t.join();
    writer.join();
}
END_NAMESPACE