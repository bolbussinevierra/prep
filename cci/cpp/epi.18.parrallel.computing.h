#pragma once

BEGIN_NAMESPACE(epi_18)
void Cout(mutex& cout_lock, string msg) {
    lock_guard<mutex> guard(cout_lock);
    cout << msg << endl;
}

void Cout(mutex& cout_lock, thread::id id, string msg) {
    lock_guard<mutex> guard(cout_lock);
    cout << id << ":" << msg << endl;
}

void SolveReaderWriterProblem() {
    vector<int> shared_mem = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int stop = false;
    mutex reader_lock;
    mutex writer_lock;
    mutex cout_lock;
    int reader_count = 0;
    bool writer_waiting = true;
    condition_variable cr, cw;

    vector<thread> writers;
    for (int i = 0; i < 2; ++i) {
        writers.emplace_back(thread([&]
        {
            default_random_engine e((random_device())());
            uniform_int_distribution<> d(0, 9);
            while (!stop) {
                {
                    lock_guard<mutex> guard(writer_lock);
                    bool written = false;
                    writer_waiting = true;

                    while (!written) {
                        unique_lock<mutex> rl(reader_lock);
                        cr.wait(rl, [&](){if (reader_count == 0) { puts("Zero!\n"); return true; } else { return false; }});
                        // once we exist wait, we own reader lock. Check if a reader snuck in
                        if (reader_count == 0) {
                            shared_mem[d(e)] = d(e);
                            written = true;
                            Cout(cout_lock, "Successfully Wrote!");
                        } else {
                            Cout(cout_lock, "Waiting for chance to write!");
                        }
                    }

                    // unblock any readers that were waiting for the writer
                    writer_waiting = false;
                    cw.notify_all();
                    this_thread::yield();
                }
            }
        }));
    }

    vector<thread> readers;
    for (int i = 0; i < 5; ++i) {
        readers.emplace_back(thread([&]()
        {
            while (!stop) {
                {
                    unique_lock<mutex> guard(reader_lock);
                    // don't starve a writer! don't allow any more incoming readers while a writer is waiting
                    cw.wait(guard, [&]() { return !writer_waiting; }); 
                    reader_count++;
                }
                Cout(cout_lock, to_string(accumulate(begin(shared_mem), end(shared_mem), 0)));
                {
                    lock_guard<mutex> guard(reader_lock);
                    reader_count--;
                }
                cr.notify_one(); // notify the writer to check condition
            }
            
        } ));
    }
    std::chrono::milliseconds dura(15000);
    std::this_thread::sleep_for(dura);
    stop = true;
    for (auto& t : readers)
        t.join();
    for (auto& t : writers)
        t.join();
}
END_NAMESPACE