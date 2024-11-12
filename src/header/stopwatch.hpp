#pragma once
#include<chrono>

namespace Time
{
    typedef std::chrono::steady_clock::time_point reference_point;
    typedef std::chrono::duration<double> duration;

    class Stopwatch
    {
        private:
            reference_point begin, end, pause_start;
            duration pause_mod;
            bool running, paused;
        
        public:
            Stopwatch() : begin(reference_point::min()),
                          end(reference_point::min()),
                          pause_start(reference_point::min()),
                          pause_mod(duration::zero()),
                          running(false), paused() {}

            void start()
            {
                begin = std::chrono::steady_clock::now();
                running = true;
            }

            void stop()
            {
                end = std::chrono::steady_clock::now();
                running = false;
            }

            double getRuntime()
            {
                if(running || begin == reference_point::min()) return -1.0;

                duration elapsed_seconds = (end - begin) - pause_mod;

                reset();
                
                return elapsed_seconds.count();
            }

            double showInRealTime()
            {
                if(begin == reference_point::min()) return -1.0;


                duration elapsed_seconds = duration::zero();

                if(paused)
                {
                    elapsed_seconds = ((running? std::chrono::steady_clock::now() : end) - begin) - pause_mod;
                }
                else
                {
                    elapsed_seconds = ((running? std::chrono::steady_clock::now() : end) - begin);
                }

                return elapsed_seconds.count();
            }

            void pause()
            {
                if(running && !paused)
                {
                    pause_start = std::chrono::steady_clock::now(); 
                    paused = true;
                }
            }

            void resume()
            {
                if(paused)
                {
                    pause_mod = std::chrono::steady_clock::now() - pause_start;
                    paused = false;
                }
            }

            void reset()
            {
                end = reference_point::min();
                begin = reference_point::min();
                pause_mod = duration::zero();
                running = false;
                paused = false;
            }
    };
}