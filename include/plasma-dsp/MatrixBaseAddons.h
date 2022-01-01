#ifndef C63AD55F_46BC_4875_BB0D_2D632194F831
#define C63AD55F_46BC_4875_BB0D_2D632194F831
inline Scalar at(uint i, uint j) const { return this->operator()(i,j); }
inline Scalar& at(uint i, uint j) { return this->operator()(i,j); }
inline Scalar at(uint i) const { return this->operator[](i); }
inline Scalar& at(uint i) { return this->operator[](i); }
inline RealScalar squaredLength() const { return squaredNorm(); }
inline RealScalar length() const { return norm(); }
inline RealScalar invLength(void) const { return fast_inv_sqrt(squaredNorm()); }
template<typename OtherDerived>
inline Scalar squaredDistanceTo(const MatrixBase<OtherDerived>& other) const
{ return (derived() - other.derived()).squaredNorm(); }
template<typename OtherDerived>
inline RealScalar distanceTo(const MatrixBase<OtherDerived>& other) const
{ return internal::sqrt(derived().squaredDistanceTo(other)); }
inline void scaleTo(RealScalar l) { RealScalar vl = norm(); if (vl>1e-9) derived() *= (l/vl); }
inline Transpose<Derived> transposed() {return this->transpose();}
inline const Transpose<Derived> transposed() const {return this->transpose();}
inline uint minComponentId(void) const  { int i; this->minCoeff(&i); return i; }
inline uint maxComponentId(void) const  { int i; this->maxCoeff(&i); return i; }
template<typename OtherDerived>
void makeFloor(const MatrixBase<OtherDerived>& other) { derived() = derived().cwiseMin(other.derived()); }
template<typename OtherDerived>
void makeCeil(const MatrixBase<OtherDerived>& other) { derived() = derived().cwiseMax(other.derived()); }
const CwiseUnaryOp<internal::scalar_add_op<Scalar>, Derived>
operator+(const Scalar& scalar) const
{ return CwiseUnaryOp<internal::scalar_add_op<Scalar>, Derived>(derived(), internal::scalar_add_op<Scalar>(scalar)); }
friend const CwiseUnaryOp<internal::scalar_add_op<Scalar>, Derived>
operator+(const Scalar& scalar, const MatrixBase<Derived>& mat)
{ return CwiseUnaryOp<internal::scalar_add_op<Scalar>, Derived>(mat.derived(), internal::scalar_add_op<Scalar>(scalar)); }


#endif /* C63AD55F_46BC_4875_BB0D_2D632194F831 */
