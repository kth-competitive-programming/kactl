#pragma once

// Taken from https://stackoverflow.com/a/40873657/2014771
template <class F> struct y_combinator {
    F f; // the lambda will be stored here

    // a forwarding operator():
    template <class... Args> decltype(auto) operator()(Args &&... args) const {
        // we pass ourselves to f, then the arguments.
        return f(std::ref(*this), std::forward<Args>(args)...);
    }
};

// helper function that deduces the type of the lambda:
template <class F> y_combinator<std::decay_t<F>> make_y_combinator(F &&f) { return {std::forward<F>(f)}; }
