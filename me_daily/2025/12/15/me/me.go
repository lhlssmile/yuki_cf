package me

import (
	"fmt"
	"sync"
)

type State struct {
	value int
}

type Operation func(s *State) error
type SafeState struct {
	mu    sync.Mutex
	value int
}

func Add(x int) Operation {
	return func(s *State) error {
		s.value += x
		return nil
	}
}

func Sub(x int) Operation {
	return func(s *State) error {
		if s.value < x {
			return fmt.Errorf("insufficient value")
		}
		s.value -= x
		return nil
	}
}
func ApplyAll(s *State, ops []Operation) error {
	snapshot := s.value
	for _, op := range ops {
		if err := op(s); err != nil {
			s.value = snapshot
			return err
		}
	}
	return nil
}
func ApplyAllSafe(s *SafeState, ops []Operation) error {
	s.mu.Lock()
	defer s.mu.Unlock()
	snapshot := s.value
	for _, op := range ops {
		if err := op((*State)(s)); err != nil {
			s.value = snapshot
			return err
		}
	}
	return nil
}
