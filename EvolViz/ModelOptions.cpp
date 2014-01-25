#include "ModelOptions.h"

#define IMPLEMENT_VISITABLE(type, visitor_type) \
void type::accept(visitor_type& visitor) const {\
	visitor.visit(*this); \
}

namespace common {
// So much 80', wow
// So define
// wow, so preprocessing
// so enterprice, wow
IMPLEMENT_VISITABLE(PointInitialization, InitializationOptionsVisitor)
IMPLEMENT_VISITABLE(RandomInitialization, InitializationOptionsVisitor)
IMPLEMENT_VISITABLE(UniversalRandomMutation, MutationOptionsVisitor)
IMPLEMENT_VISITABLE(GaussRandomMutation, MutationOptionsVisitor)
IMPLEMENT_VISITABLE(ConstMutation, MutationOptionsVisitor)
IMPLEMENT_VISITABLE(ConstAvgCrossOver, CrossOverOptionsVisitor)
IMPLEMENT_VISITABLE(UniversalRandomAvgCrossOver, CrossOverOptionsVisitor)
IMPLEMENT_VISITABLE(GaussRandomAvgCrossOver, CrossOverOptionsVisitor)
IMPLEMENT_VISITABLE(UniversalRandomFixedCrossOver, CrossOverOptionsVisitor)
IMPLEMENT_VISITABLE(RollingRangeAlignment, RangeAlignmentOptionsVisitor)
IMPLEMENT_VISITABLE(MirroringRangeAlignment, RangeAlignmentOptionsVisitor)
IMPLEMENT_VISITABLE(UniversalRandomReinitializationAlignment, RangeAlignmentOptionsVisitor)
IMPLEMENT_VISITABLE(EliteSelection, SelectionOptionsVisitor)
IMPLEMENT_VISITABLE(LoterySelection, SelectionOptionsVisitor)
IMPLEMENT_VISITABLE(TournamentSelection, SelectionOptionsVisitor)
IMPLEMENT_VISITABLE(RouletteSelection, SelectionOptionsVisitor)
} // namespace model